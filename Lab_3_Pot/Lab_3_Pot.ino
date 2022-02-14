void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int readVal = analogRead(A0);
  delay(5);
  
  Serial.print("Read value (0 - 1023): ");
  Serial.println(readVal);
  delay(5);

  int writeVal = map(readVal, 0, 1023, 0, 255);
  delay(5);
  
  Serial.print("Write value (0 - 255): ");
  Serial.println(writeVal);
  delay(5);
  
  analogWrite(3, writeVal);
  delay(20);
}
