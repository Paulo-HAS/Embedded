
const int pinLed = 13;

void setup() {
    Serial.begin(9600);
    pinMode(pinLed, OUTPUT);
}

void loop() {
    if(Serial.available() > 0){
        char command = Serial.read();

        if(command == '1'){
            digitalWrite(pinLed, HIGH);
        }
        else if(command == '0'){
            digitalWrite(pinLed, LOW);
        }
    }
}