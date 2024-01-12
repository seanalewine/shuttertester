
// Analog input 0 is used to measure the voltage across the IR-receiver
static constexpr int pin = A0;

int sensorValue = 0;
unsigned long start = 0;
unsigned long stop = 0;
bool isOpen = false;
bool test = true;
int threshold = 0;

void setup() {
   Serial.begin(9600);
  threshold = setThreshold();
  Serial.println("Threshold Set Successfully.");
  Serial.println("Fire shutter to calculate speed.");
}

void loop() {

   sensorValue = analogRead(pin);
   
   // shutter opens
   if ( sensorValue < threshold && ! isOpen) {
      start = micros();
      isOpen = true;
   }
   // Shutter closes
   else if ( sensorValue > threshold && isOpen ) {
      stop = micros();
     unsigned long mstime = ((stop - start)/1000);
      Serial.print(mstime);
      Serial.println(" ms");
      isOpen = false;
   }

}


int setThreshold() {
   Serial.println("Calculating Ambient Light. Do not open shutter for 10 seconds.");
   int minValue = 0;
   int i = 0;
   while (i < 20) {
      if (analogRead(pin) < minValue) {
         minValue = analogRead(pin);
         i+= 1;
         delay(500);
      }
   return(minValue);
   }
}
