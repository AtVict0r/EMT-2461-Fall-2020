/* Pins */
const byte 
LED = 11,

/* Constant values */
minVal = 0, aMaxVal = 255;

const int
dMaxVal = 1023, waitTime = 333;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int pResistorVal = analogRead(A0);

  Serial.print("Read value (0 - 1023): ");
  Serial.println(pResistorVal);
  delay(waitTime);
  
  byte wLED = map(pResistorVal, minVal, dMaxVal, aMaxVal, minVal);

  Serial.print("Write value (255 - 0): ");
  Serial.println(wLED);
  delay(waitTime);
  
  analogWrite(LED, wLED);
  delay(waitTime); // Wait for 1000 millisecond(s)
}
