
const byte redpin = 5; //select the pin for the red LED
const byte bluepin = 6; // select the pin for the  blue LED
const byte greenpin = 7;// select the pin for the green LED
 

 
void setup() 
{
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
}
 
void loop() 
{
  light(255, 0, 0);

  light(0, 255, 0);
   
  light(0, 0, 255); 
}

void light(byte LED1, byte LED2, byte LED3) 
{
  analogWrite(redpin, LED1);
  analogWrite(bluepin, LED2);
  analogWrite(greenpin, LED3);

  delay(500);
}
