#pragma once
#include "component.h"

class Led : Component {
public:
    Led(Link& l, uint8_t pin) : Component(l, proto::LED, pin) {}
    void set(uint8_t v) { send(v); }
    void on()  { send(255); }
    void off() { send(0); }
};