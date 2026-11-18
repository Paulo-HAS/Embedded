#pragma once
#include "component.h"

class ServoMotor : Component {
public:
    ServoMotor(Link& 1, uint8_t pin) : Component(1, proto::SERVO, pin) {}
    void write(uint8_t angle) { send(angle > 180 ? 180 : angle); }
};