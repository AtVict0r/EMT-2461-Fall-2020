// include the library code:
#include <LiquidCrystal.h>

const int trigPin = 12, echoPin = 11, MAX_DISTANCE = 200, soundVelocity = 340, DELAY_TIMER = 1000,
red = 10, blue = 9, green = 8;
const float timeOut = MAX_DISTANCE * 60;
int count = 0;
float distance, temperatureVoltage = analogRead(pin) * 0.004882814, temperatureC = (temperatureVoltage - 0.5) * 100.0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(DELAY_TIMER);
}

void loop() {
  distance = getSonar();

  lcd.clear();
  lcd.print("Menu: ");
  lcd.setCursor(0, 1);
  lcd.print("1 Distance(CM)");
  delay(DELAY_TIMER/2);
  
  lcd.clear();
  lcd.print("2 Distance(IN)");
  lcd.setCursor(0, 1);
  lcd.print("3 Distance(RBG)");
  delay(DELAY_TIMER/2);
  
  lcd.clear();
  lcd.print("4 Temperature(C)");
  lcd.setCursor(0, 1);
  lcd.print("5 Temperature(F)");
  delay(DELAY_TIMER/2);
  
  lcd.clear();
  lcd.print("6 Temperature(K)");
  lcd.setCursor(0, 1);
  lcd.print("7 Light Show");
  delay(DELAY_TIMER/2);
  
  lcd.clear();
  lcd.print("8 Uptime");
  lcd.setCursor(0, 1);
  lcd.print("9 Exit");
  delay(DELAY_TIMER/2);
}

void serialEvent() {
  if(Serial.available()) {

    char choice = Serial.read();

    switch (choice) {
      case '1':{
      	showDistance_cm();
    	  break;
      }
  	  case '2':{
      	showDistance_in();
    	  break;
      }      
      case '3':{
        lcd.clear();
      	showDistance_rbg();
    	  break;
      }
  	  case '4':{
      	showTemperature_c();
    	  break;
      }      
      case '5':{
      	showTemperature_f();
    	  break;
      }
  	  case '6':{
      	showTemperature_k();
    	  break;
      }      
      case '7':{
        lcd.clear();
      	changeColor();
    	  break;
      }
  	  case '8':{
      	lcd.clear();
        lcd.print(millis()/1000);
        delay(DELAY_TIMER/4);
        lcd.clear();
    	  break;
      }     
      case '9':
    	  break;
      default:{
        lcd.clear();
        lcd.print("Invalid Option!");
        delay(DELAY_TIMER/4);
        lcd.clear();
    	  break;
      }
	  }
  }
}

void showDistance_cm() {
  lcd.clear();
  lcd.print("Distance(CM):");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("cm");
}

void showDistance_in() {
  lcd.clear();
  lcd.print("Distance(IN):");
  lcd.setCursor(0, 1);
  lcd.print(distance * 0.3937);
}

void showDistance_rbg() {
  const float max = 334.8, far = 223.2, mid = 111.6;
    
  lcd.clear();
  
  if(distance <= mid)
    rgbShowGreen();
  else if(distance > mid && distance <= far)
    rgbShowWhite();
  else if(distance > far && distance <= max)
    rgbShowRed();
  else
    rgbShowBlue();
    
  delay(DELAY_TIMER);
}

void showTemperature_c() {
  lcd.clear();
  lcd.print("Temperature(C):");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC);
}

void showTemperature_f() {
  lcd.clear();
  lcd.print("Temperature(F):");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC * 1.8 + 32);
}

void showTemperature_k() {
  lcd.clear();
  lcd.print("Temperature(K):");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC + 273.15);
}

float getSonar() {
  unsigned long pingTime;
  float distance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pingTime = pulseIn(echoPin, HIGH, timeOut);
  distance = (float) pingTime * soundVelocity / 2 / 10000;

  return distance;
}

void rgbShowGreen(){
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
}

void rgbShowWhite(){
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
}
 
void rgbShowRed(){
  digitalWrite(red, HIGH);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
}
  
void rgbShowBlue(){
  digitalWrite(red, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
}

void changeColor(){
  rgbShowRed();
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  
  rgbShowBlue();
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  
  digitalWrite(red, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  
  rgbShowGreen();
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  
  digitalWrite(red, HIGH);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);  
 
  rgbShowWhite();
  
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
}
 