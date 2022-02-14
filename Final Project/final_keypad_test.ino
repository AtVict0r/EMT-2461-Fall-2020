// include the library code:
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

// initialize the library with the numbers of the interface pins
OneWire_Analog_KeyPad_3x3 keypad(5);

const int keyPadValue[] = {249, 255, 133, 311, 321, 175, 695, 745, 559};

void setup()
{
    Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
    keypad.setKeyValue(keyPadValue);
}

void loop()
{
    keypad.testKeyPad();
}