// include the library code:
class HC_SR04
{
    private:
    int trig, echo;

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
   
    public:
    HC_SR04(int trigPin, int echoPin){
        trig = trigPin;
        echo = echoPin;
    }

    void begin(){
        pinMode(trig, OUTPUT); // Sets the trigPin as an OUTPUT
        pinMode(echo, INPUT); // Sets the echoPin as an INPUT
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

// initialize the library with the numbers of the interface pins
HC_SR04 sonic(10, 9);

void setup()
{
    Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
    sonic.begin();
}

void loop()
{
    sonic.testSensor_Serial();
}