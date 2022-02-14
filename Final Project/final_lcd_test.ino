// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void setup()
{
    lcd.begin(16, 2); // lcd starts with resolution 16x2
}

void loop()
{
    lcd.clear();
    lcd.print("Count: ");
    lcd.print(millis() / 1000);
  	delay(1000);
}