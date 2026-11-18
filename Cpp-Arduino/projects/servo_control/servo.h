#pragma once
#include "component.h"

class ServoMotor : Component {
public:
    ServoMotor(Link& l, uint8_t pin) : Component(l, proto::SERVO, pin) {}
    void write(uint8_t angle) { send(angle > 180 ? 180 : angle); }
};