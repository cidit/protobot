#pragma once
#include "sensor.hpp"
#include <IRremote.h>

using Code = int;
class Infrared : Sensor<Code>
{
private:
    static int* _receive_pin;
    static Infrared *instance;
    Infrared();
protected:
    void begin() override;

public:
    static void setReceivePin(int pin);
    static Infrared *getInstance();
    bool sample(Code &out) override;
};
