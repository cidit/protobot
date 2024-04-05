#pragma once
#include "sensor.hpp"

using Meters = float;
class Ultrasound : Sensor<Meters>
{
private:
    int _echo_pin, _trigger_pin;

public:
    Ultrasound(int _echo_pin, int _trigger_pin);
    void begin() override;
    bool sample(Meters &out) override;
};