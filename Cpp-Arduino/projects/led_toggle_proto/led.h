#pragma once
#include "linkwin.h"

class Led {
    Link& link;
    uint8_t pin;
public:
    Led(Link& l, uint8_t p) : link(l), pin(p) {}
    void set(uint8_t v) { link.send(proto::make(proto::LED, pin, v)); }
    void on()  { set(255); }
    void off() { set(0); }
};