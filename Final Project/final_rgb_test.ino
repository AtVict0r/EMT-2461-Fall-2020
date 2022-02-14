// include the library code:
class RBG_LED 
{
    private:
    int red, blue,  green;

    void led_on(int redLED, int blueLED, int greenLED) {
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

// initialize the library with the numbers of the interface pins
RBG_LED rbg(2, 1, 0);

void setup()
{
    rbg.begin();
}

void loop()
{
    rbg.testLED();
}