#include <iostream>
#include <windows.h>
#include <stdint.h>

using namespace std;



class LEDDigital{
    private:
        const HANDLE* phSerial;
        const int led_pin;
        bool led_on;
        // struct padrao de mensagens
        struct {
            char type;
            int pin;
            bool set_high;
            int setPwm;
        } msg;

    public:
        // contrutor da classe, recebe o handle da port e o pino do LED
        LEDDigital(HANDLE* ph, int lp):
            phSerial(ph),
            led_pin(lp)
        { }
        // checa se o LED ja está ligado
        const bool isLedOn(){
            return led_on;
        }
        // seta o led no valor informado
        void setLed(bool c){
            DWORD bytesWritten;
            led_on = c;
            msg.pin = led_pin;
            msg.set_high = c;
            msg.setPwm = 0;
            WriteFile(*phSerial, &msg, 1, &bytesWritten, NULL);
            return;
        }

        const readmsg ledInfo(){
            // leitura no arduino das informações do led
            // readmsg é uma mnsagem de leitura de componentes na placa
            return r;
        }

}