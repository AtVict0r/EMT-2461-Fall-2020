// include the library code:
#include <LiquidCrystal.h>

class RBG_LED 
{
    private:
    int red, blue,  green;

    void led_on(bool redLED, bool blueLED, bool greenLED) {
        digitalWrite(red, redLED);
        digitalWrite(blue, blueLED);
        digitalWrite(green, greenLED);
    }

    public:
    RBG_LED(int redPin, int bluePin, int greenPin){
        red = redPin;
        blue = bluePin;
        green = greenPin;
    }

    void begin() {
        pinMode(red, OUTPUT);
        pinMode(blue, OUTPUT);
        pinMode(green, OUTPUT);
    }

    void led_off() {
        led_on(0, 0, 0);
    }

    void led_red() {
        led_on(1, 0, 0);
    }

    void led_blue() {
        led_on(0, 1, 0);
    }

    void led_green() {
        led_on(0, 0, 1);
    }

    void led_skyBlue() {
        led_on(0, 1, 1);
    }

    void led_purple() {
        led_on(1, 0, 1);
    }

    void led_yellow() {
        led_on(1, 1, 0);
    }

    void led_white() {
        led_on(1, 1, 1);
    }

    void testLED() {
        led_white();
        delay(500);
        led_yellow();
        delay(500);
        led_purple();
        delay(500);
        led_skyBlue();
        delay(500);
        led_green();
        delay(500);
        led_blue();
        delay(500);
        led_red();
        delay(500);
        led_off();
    }
};

class HC_SR04
{
    private:
    int trig, echo;
   
    public:
    HC_SR04(int trigPin, int echoPin){
        trig = trigPin;
        echo = echoPin;
    }

    void begin(){
        pinMode(trig, OUTPUT); // Sets the trigPin as an OUTPUT
        pinMode(echo, INPUT); // Sets the echoPin as an INPUT
    }

    long duration(){
        // Clears the trigPin condition
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        return pulseIn(echo, HIGH);
    }

    long distance_cm(){
        // Calculating the distance
        return duration() / 29 / 2; // Speed of sound wave divided by 2 (go and back)
    }

    long distance_in(){
        // Calculating the distance
        return duration() / 73 / 2; // Speed of sound wave divided by 2 (go and back)
    }

    void testSensor_Serial(){
        Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
        
        // Displays the distance in cm on the Serial Monitor
        Serial.print("Distance: ");
        Serial.print(distance_cm());
        Serial.println(" cm");

        // Displays the distance in inches on the Serial Monitor
        Serial.print("Distance: ");
        Serial.print(distance_in());
        Serial.println(" inch");
    }
};

class Motor_Driver_595
{
    private:
    int clock, latch, data;

    void Output_595(byte message){
        // Output low level to latchPin
        digitalWrite(latch, LOW);
        // Send serial data to 74HC595
        shiftOut(data, clock, MSBFIRST, message);
        // Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
        digitalWrite(latch, HIGH);
    }

    public:
    Motor_Driver_595(int dataPin, int latchPin, int clockPin){
        clock = clockPin;
        latch = latchPin;
        data = dataPin; 
    }

    void begin(){
        pinMode(clock, OUTPUT);
        pinMode(latch, OUTPUT);
        pinMode(data, OUTPUT);
    }

    void turnOff(){
        Output_595(0x0); // 0000 0000
    }

    void turnOn(){
        Output_595(0x1); // 0000 0001
    }

    void forward(){
        Output_595(0x51); // 0101 0001
    }

    void reverse(){
        Output_595(0xA1); // 1010 0001
    }

    void left(){
        Output_595(0x11); // 0001 0001
    }

    void right(){
        Output_595(0x41); // 0100 0001
    }
};

class OneWire_Analog_KeyPad_3x3
{
    private:
    int keyPad_Map[9][2] = {{1, 1}, {2, 2}, {3, 3},
                         {4, 4}, {5, 5}, {6, 6},
                         {7, 7}, {8, 8}, {9, 9}
                         };
    int analogPin, keyValue_Past = -1;

    public:
    OneWire_Analog_KeyPad_3x3(int pin){
        analogPin = pin;
    }
    
    void setKeyValue(int arr[]){
        for(int i = 0; i < 9; i++){
            keyPad_Map[i][1] = arr[i];
        }
    }

    int getInput(){
        int findValue = analogRead(analogPin);

        for(int i = 0; i < 9; i++){
            if(findValue == keyPad_Map[i][1]){
                return keyPad_Map[i][0];
            }
        }
    }

    void findKeyPadValue() {
        int keyValue_Current = analogRead(analogPin);
        
      	if(keyValue_Current != keyValue_Past){
        	Serial.print("Key Value is ");
            Serial.println(keyValue_Past);
            
            keyValue_Past = keyValue_Current;
        }
      
      	delayMicroseconds(2);
    }
  
  	void testKeyPad() {
      int keyValue_Current = getInput();
      
      if(keyValue_Current >= 1 && keyValue_Current <= 9 && keyValue_Current != keyValue_Past) {
        Serial.print("Key Value is ");
        Serial.println(keyValue_Current);
        
        keyValue_Past = keyValue_Current;
      }
    }
};

class Photoresistor
{
    private:
    int analogPin = 0, previous = -1;

    public:
    Photoresistor(int pin){
        analogPin = pin;
    }

    int getInput() {
        int analogValue = analogRead(analogPin) / 2;
        int percentageValue = map(analogValue, 0, 511, 0, 100);
        return percentageValue;
    }

    void testInput(){
        int current = getInput();
        if(previous != current){
            previous = current;
            Serial.print("Brightness is ");
            Serial.println(previous);
        }
    }
};

// initialize the library with the numbers of the interface pins
RBG_LED rbg(2, 1, 0);
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
HC_SR04 sonic(10, 9);
Motor_Driver_595 motor(13, 12, 11);

OneWire_Analog_KeyPad_3x3 keypad(5);
Photoresistor brightness(0);

int keyPadValue[] = {249, 255, 133, 311, 321, 175, 695, 745, 559}; 

void setup()
{
    Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
    lcd.begin(16, 2); // lcd starts with resolution 16x2
    rbg.begin();
    sonic.begin();
    motor.begin();

    keypad.setKeyValue(keyPadValue);
    
    motor.turnOn();
    lcd.clear();
}

void loop()
{
    display_lcdMenu_Main();
    int choice = keypad.getInput();
    mainMenuChoice(choice);

    delay(1000);
}

void display_lcdMenu_Main(){
    const String mainMenuOptions[] = {"Menu", "Sonic Sensor", "Photoresistor", "Exit"};

    for(int i = 0; i < 4; i+=2){
        lcd.clear();
        lcd.print(i+1);
        lcd.print(") ");
        lcd.print(mainMenuOptions[i]);

        lcd.setCursor(0, 1);
        lcd.print(i+2);
        lcd.print(") ");
        lcd.print(mainMenuOptions[i+1]);

        delay(1000);
    }

    lcd.clear();
    lcd.print("Choose: ");
}

void display_lcdMenu_Sonic(){
    const String sonicMenuOptions[] = {"Menu", "CM", "Inches", "RBG", "Back",  "Exit"};

    for(int i = 0; i < 6; i+=2){
        lcd.clear();
        lcd.print(i+1);
        lcd.print(") ");
        lcd.print(sonicMenuOptions[i]);

        lcd.setCursor(0, 1);
        lcd.print(i+2);
        lcd.print(") ");
        lcd.print(sonicMenuOptions[i+1]);

        delay(1000);
    }

    lcd.clear();
    lcd.print("Choose: ");

    int choice = keypad.getInput();
    sonicChoice(choice);

}

void mainMenuChoice(int option){
    lcd.clear();

    switch (option) {
  	  case 2:{
      	display_lcdMenu_Sonic();
    	break;
      }      
      case 3:{
        lcd_ShowPhotoresistor();
    	break;
      }     
      default:{
        display_lcdMenu_Main();
      }
	}
}

void sonicChoice(int option){
    lcd.clear();

    switch (option) {
  	  case 2:{
      	lcd.print(sonic.distance_cm());
    	break;
      }      
      case 3:{
        lcd.print(sonic.distance_in());;
    	break;
      }   
      case 4:{
        showDistance_rbg();
    	break;
      }  
      default:{
        display_lcdMenu_Main();
      }
	}
}

void lcd_ShowPhotoresistor(){
    lcd.clear();
    lcd.print("Brightness: ");
    lcd.print(brightness.getInput());
    lcd.print('%');
}

void showDistance_rbg() {
  const int max = 334, far = 223, mid = 111;
  int distance = sonic.distance_cm();
    
  lcd.clear();
  
  if(distance <= mid)
    rbg.led_green();
  else if(distance > mid && distance <= far)
    rbg.led_white();
  else if(distance > far && distance <= max)
    rbg.led_red();
  else
    rbg.led_blue();
    
  delay(1000);
}