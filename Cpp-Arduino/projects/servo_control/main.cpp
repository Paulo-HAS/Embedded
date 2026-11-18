#include <chrono>
#include <iostream>
#include <thread>
#include "led.h"
#include "servo.h"

int main() {
    using namespace std::chrono_literals;
    Link link("\\\\.\\COM3");               // ou "/dev/ttyACM0"
    std::cout << "Conectando ao Arduino..." << std::endl;
    std::this_thread::sleep_for(2s);        // abrir a porta reinicia o Arduino

    Led led(link, 13);
    ServoMotor servo(link, 9);
    
    uint8_t ref = 0;
    servo.write(0);
    led.on();
    while(true){
        if(ref > 360) ref = 0;
        if(ref > 180) servo.write(360 - ref);
        else servo.write(ref++);
        std::this_thread::sleep_for(0.1s);
    }
    led.off();
}