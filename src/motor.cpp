#include <Arduino.h>
#include "motor.hpp"

Motor::Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin) : _speed_pin(speed_pin), _clockwise_pin(clockwise_pin), _counter_clockwise_pin(counter_clockwise_pin)
{
    this->_calibration = 1;
}

Motor::Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin, float calibration)
{
    this->setCalibration(calibration);
}

void Motor::begin()
{
    pinMode(this->_speed_pin, OUTPUT);
    pinMode(this->_clockwise_pin, OUTPUT);
    pinMode(this->_counter_clockwise_pin, OUTPUT);
}

void Motor::halt()
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
    magnitude = (magnitude > 1 ? 1 : magnitude) * this->_calibration;
    const auto PWM_MAX_VALUE = 255;
    auto pwm_speed = int(magnitude * PWM_MAX_VALUE);
    analogWrite(this->_speed_pin, pwm_speed);
}

void Motor::setCalibration(float calibration)
{
    if (calibration > 1)
    {
        if (Serial)
        {
            Serial.println("calibration du moteur trops haute! " + String(calibration));
        }
        _calibration = 1;
    }
    else if (calibration < 0)
    {
        if (Serial)
        {
            Serial.println("calibration du moteur trops basse! " + String(calibration));
        }
        _calibration = 0;
    }
    else
    {
        _calibration = calibration;
    }
}

float Motor::getCalibration() {
    return this->_calibration;
}
