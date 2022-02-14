#include <Servo.h>
Servo myservo;

const int servoPin = 5, ledPin = 6, potPin = A0;
int current_servoPos = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  myservo.attach(servoPin);
  myservo.write(current_servoPos);
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);
  int potVal = analogRead(potPin);
  
  int ledDimVal = map(potVal, 0, 1023, 0, 255);
  analogWrite(ledPin, ledDimVal);
  
  current_servoPos = moveServo(potVal, current_servoPos);
  
  serialWrite(current_servoPos, potVal);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

int moveServo(int potVal, int current_servoPos){
  int servoPos = map(potVal, 0, 1023, 0, 180);
  
  if(servoPos > current_servoPos){
    for(int i = current_servoPos; i <= servoPos; i+=5){
      myservo.write(i);
      delay(15);
    }
  } else {
    for(int i = current_servoPos; i >= servoPos; i-=5){
      myservo.write(i);
      delay(15);
    }
  }
  
  return servoPos;
}

void serialWrite(int current_servoPos, int potVal){
  Serial.print("Position (angle in degree): ");
  Serial.println(current_servoPos);
  Serial.print("Read value (from analog input): ");
  Serial.println(potVal);
  Serial.println("------------------------------");
  
  delay(500);
}