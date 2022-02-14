#include <LiquidCrystal.h>
#include "SR04.h"

  const int   TRIG_PIN = 8,
/*const int*/ ECHO_PIN = 9,
/*const int*/ RS_PIN = 12,
/*const int*/ ENABLE_PIN = 11,
/*const int*/ D7_PIN = 2,
/*const int*/ D6_PIN = 3,
/*const int*/ D5_PIN = 4,
/*const int*/ D4_PIN = 5,
/*const int*/ LCD_COLUMN = 16,
/*const int*/ LCD_ROW = 2,
/*const int*/ SERIAL_SPEED = 9600,
/*const int*/ DELAY_TIMER = 1000;

int before = 0;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

void setup() {
   Serial.begin(SERIAL_SPEED);
   
   lcd.begin(LCD_COLUMN, LCD_ROW);

   delay(DELAY_TIMER);
}

void loop() {
   int after = sr04.Distance();
   
   do {
    lcd.clear();
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(before);
    lcd.print("cm");

    Serial.print(before);
    Serial.println("cm");

    before = after;
   } while(before != after);
      
   delay(DELAY_TIMER);
}

void serialEvent() {
  if(Serial.available()) {
    String word = Serial.readString();
    // set the cursor to column 0, line 0:
    lcd.clear();
    // print out the value at LCD Display:
  	lcd.print(word);
  	// print out the value at Serial Monitor:
    Serial.print("UNO received: '");
  	Serial.print(word);
    Serial.println("'");
  }

  delay(DELAY_TIMER);
  lcd.clear();
}
