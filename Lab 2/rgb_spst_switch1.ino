int switchState = 0;

void setup()
{
  pinMode(2, INPUT);

  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  switchState = digitalRead(2);
  if (switchState == HIGH) {
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
  delay(1000); // Wait for 1000 millisecond(s)
}
