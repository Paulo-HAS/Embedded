#include <Servo.h>
#include "protocol.h"

using namespace proto;  

Servo servos[MAX_SERVOS];
uint8_t servoPins[MAX_SERVOS];
uint8_t servoCount = 0;

// função de atuação dos servos
void moveServo(uint8_t pin, uint8_t angle) {
    for (uint8_t i = 0; i < servoCount; i++)
        if (servoPins[i] == pin) {servos[i].write(angle); return; }
    if (servoCount < MAX_SERVOS) {
        servoPins[servoCount] = pin;
        servos[servoCount].attach(pin);
        servos[servoCount++].write(angle);
    }
}


void handle(const Msg &m) {
    switch (m.type) {
        case LED:
        pinMode(m.pin, OUTPUT);
        analogWrite(m.pin, m.value);
        break;
        case SERVO:
            moveServo(m.pin, m.value);
            break;
    }
}

void setup () { 
    Serial.begin(115200); 
}

void loop() {
    // static = mantem valor da variável entre ciclos do loop
    static Msg m;
    static uint8_t n = 0;   //bytes recebidos na mensagem
    while (Serial.available()) {    // verifica sem tem algo no buffer
        uint8_t b = Serial.read();  //lê UM byte do buffer
        if (n == 0 && b != SYNC) continue;  //descarta o byte lido se estiver no início e não for SYNC
        reinterpret_cast<uint8_t*>(&m)[n++] = b;    //grava o byte na mensagem, reinterpret_cast trata o struct como um vet de bytes
        if (n == sizeof m) {    //verifica se terminou a mensagem
            n = 0;
            if (m.crc == checksum(m)) handle(m);    //verifica se o crc bate com o recebido
        }
    }
}


