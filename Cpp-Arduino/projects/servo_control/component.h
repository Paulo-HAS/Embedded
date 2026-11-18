#pragma once
#include "linkwin.h"

class Component {
    Link& link;
    proto::Type type;
    uint8_t pin;
protected:
    Component(Link& l, proto::Type t, uint8_t p) : link(l), type(t), pin(p) {}
    void send(uint8_t value) { link.send(proto::make(type, pin, value)); }
};