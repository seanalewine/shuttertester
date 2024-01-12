
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
  
  int sensorValue1 = 0;
  int sensorValue2 = 0;
  int sensorValue3 = 0;
  Serial.println("Calculating Ambient Light. Do not open shutter");
  delay(500);
  sensorValue1 = analogRead(pin);
  Serial.println(sensorValue1);
  delay(500);
  sensorValue2 = analogRead(pin);
  Serial.println(sensorValue1);
  delay(500);
  sensorValue3 = analogRead(pin);
  Serial.println(sensorValue1);
  delay(500);
  Serial.println("If values are significantly different, reset and try again.");
  delay(500);
  return((sensorValue1+sensorValue2+sensorValue3)/3);
  
}
