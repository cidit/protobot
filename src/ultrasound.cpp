#include <Arduino.h>
#include "ultrasound.hpp"

Ultrasound::Ultrasound(int echo_pin, int trigger_pin)
    : _echo_pin(echo_pin), _trigger_pin(trigger_pin) {}

void Ultrasound::begin()
{
    pinMode(this->_echo_pin, INPUT);
    pinMode(this->_trigger_pin, OUTPUT);
}

bool Ultrasound::sample(Meters &out)
{
    // implementation basée sur le code des examples.
    digitalWrite(this->_trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->_trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_trigger_pin, LOW);
    float fdist = pulseIn(this->_echo_pin, HIGH);
    out = fdist / 58 * 100;
    return true;
}
