// include the library code:
class Photoresistor
{
    private:
    const int analogPin = 0, analogMin = 0, analogMax = 1023, brightnessMin = 0, brightnessMax = 100;
    int previous = -1;

    public:
    Photoresistor(int pin){
        analogPin = pin;
    }

    int getInput() {
        int analogValue = analogRead(analogPin);
        int percentageValue = map(analogValue, analogMin, analogMax, brightnessMin, brightnessMax);
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
Photoresistor brightness(0);

void setup()
{
    Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}

void loop()
{
    brightness.testInput();
}