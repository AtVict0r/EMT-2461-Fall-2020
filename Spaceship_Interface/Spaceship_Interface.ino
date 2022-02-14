#define SWITCH 2 // Assign pin 2 to Push Button

#define LED_1 4 // Assign pin 4 to LED 1
#define LED_2 6 // Assign pin 6 to LED 2
#define LED_3 8 // Assign pin 8 to LED 3

bool switchState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH, INPUT_PULLUP); // Use built-in resistor for push button
  
  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  Test_LED(); // Check if LED is working
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(SWITCH);
  
  if(switchState){
    // if button is not pushed
    Light_Up(0, 0, 1, 250);

    Light_Up_S(1, 0, 250);
  } else {
    // if button is pushed
    Light_Up(1, 0, 0);
  }
}

void Test_LED() {
  Light_Up(0, 0, 0, 1000);

  Light_Up(1, 1, 1, 2000); // Test All LED

  Light_Up(0, 0, 0, 1000);

  Light_Up(1, 0, 0, 500); // Test LED 1

  Light_Up(0, 1, 0, 500); // Test LED 2

  Light_Up(0, 0, 1, 500); // Test LED 3

  Light_Up(0, 0, 0, 1000);
}

void Light_Up(bool LED_1_Val, bool LED_2_Val, bool LED_3_Val){
  digitalWrite(LED_1, LED_1_Val);
  digitalWrite(LED_2, LED_2_Val);
  digitalWrite(LED_3, LED_3_Val);
}

void Light_Up(bool LED_1_Val, bool LED_2_Val, bool LED_3_Val, int mSec){
  Light_Up(LED_1_Val, LED_2_Val, LED_3_Val);

  delay(mSec);
}

void Light_Up_S(bool LED_2_Val, bool LED_3_Val, int mSec){
  digitalWrite(LED_2, LED_2_Val);
  digitalWrite(LED_3, LED_3_Val);

  delay(mSec);
}
