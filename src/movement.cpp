#include "movement.hpp"

#include <Arduino.h>

Motor::Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin) : _speed_pin(speed_pin), _clockwise_pin(clockwise_pin), _counter_clockwise_pin(counter_clockwise_pin) {}

void Motor::begin()
{
    pinMode(this->_speed_pin, OUTPUT);
    pinMode(this->_clockwise_pin, OUTPUT);
    pinMode(this->_counter_clockwise_pin, OUTPUT);
}

void Motor::stop()
{
    setSpeed(0);
}

void Motor::setClockwise()
{
    digitalWrite(this->_clockwise_pin, HIGH);
    digitalWrite(this->_counter_clockwise_pin, LOW);
}

void Motor::setCounterClockwise()
{
    digitalWrite(this->_clockwise_pin, LOW);
    digitalWrite(this->_counter_clockwise_pin, HIGH);
}

void Motor::setSpeed(float speed)
{
    if (speed < 0)
    {
        setCounterClockwise();
    }
    else
    {
        setClockwise();
    }
    auto magnitude = abs(speed);
    magnitude = magnitude > 1 ? 1 : magnitude;
    const auto PWM_MAX_VALUE = 255;
    auto pwm_speed = int(magnitude * PWM_MAX_VALUE);
    analogWrite(this->_speed_pin, pwm_speed);
}