#pragma once
#include "math.hpp"

class Motor
{
private:
    int _speed_pin;
    int _clockwise_pin;
    int _counter_clockwise_pin;
    void setClockwise();
    void setCounterClockwise();

public:
    Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin);
    void begin();
    void halt();

    /**
     * expects speed between -1 and 1
     */
    void setSpeed(float speed);
};

class WheelSystem
{
private:
    Motor _left, _right;

public:
    WheelSystem(Motor left, Motor right);
    void begin();
    void setMovement(Vector movement);
    void halt();
};