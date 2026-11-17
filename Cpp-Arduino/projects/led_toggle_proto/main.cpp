#include <chrono>
#include <iostream>
#include <thread>
#include "led.h"

int main() {
    using namespace std::chrono_literals;
    Link link("\\\\.\\COM3");
    std::cout << "Conectando ao Arduino..." << std::endl;
    std::this_thread::sleep_for(2s);  // abrir a porta reinicia o Arduino
    
    char op;
    Led led(link, 13);
    while(true){
        std::cout << "Digite 1 (ligar), 0 (desligar) ou s (sair):" << std::endl;
        std::cin >> op;
        
        if(op == 's' || op == 'S') break;
        else if(op == '1') led.on();
        else if(op == '0') led.off();
    }
}