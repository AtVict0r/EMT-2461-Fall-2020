// include the library code:
class Motor_Driver_595
{
    private:
    int clock, latch, data;

    void 595_Output(byte message){
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
        595_Output(0x0); // 0000 0000
    }

    void turnOn(){
        595_Output(0x1); // 0000 0001
    }

    void forward(){
        595_Output(0x51); // 0101 0001
    }

    void reverse(){
        595_Output(0xA1); // 1010 0001
    }

    void left(){
        595_Output(0x11); // 0001 0001
    }

    void right(){
        595_Output(0x41); // 0100 0001
    }
};

// initialize the library with the numbers of the interface pins
Motor_Driver_595 motor(13, 12, 11);

void setup()
{
    motor.begin();
}

void loop()
{
    motor.turnOn();
}