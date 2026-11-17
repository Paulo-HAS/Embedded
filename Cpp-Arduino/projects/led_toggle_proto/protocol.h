#pragma once // evita dupla compilação do arquivo
#include <stdint.h>

namespace proto{    // criando namespace custom

    constexpr uint8_t SYNC = 0xAA;  // byte marcador de início de mensagem, mantem o sincronismo
    enum Type : uint8_t { LED = 1 }; // lista dos tipos de componentes

    struct Msg {    // mensagem de 5 bytes na ordem de stream do serial
        uint8_t sync, type, pin, value, crc;    // crc = checksum para verificar erro
    };
    static_assert(sizeof(Msg) == 5, "Msg com padding"); //verifica se foi feito padding na mensagem

    // calcula o crc fazendo XOR nos bytes
    // inline permite definir uma função sem que ocorra definição multipla
    inline uint8_t checksum(const Msg &m) { return m.sync ^ m.type ^ m.pin ^ m.value; }

    // construção da mensagem
    inline Msg make(uint8_t type, uint8_t pin, uint8_t value) {
        Msg m{SYNC, type, pin, value, 0};
        m.crc = checksum(m);
        return m;
    }
}