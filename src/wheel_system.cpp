#include "wheel_system.hpp"
#include "math.hpp"
#include <Arduino.h>


WheelSystem::WheelSystem(Motor left, Motor right) : _left(left), _right(right) {}

void WheelSystem::begin()
{
    this->_left.begin();
    this->_right.begin();
}

void WheelSystem::setMovement(Vector movement)
{

    auto slowest = movement.x;
    auto fastest = hypot(movement.x, movement.y) * (movement.y / abs(movement.y));

    if (movement.x > 0)
    {
        this->_left.setSpeed(-fastest);
        this->_right.setSpeed(slowest);
    }
    else if (movement.x < 0)
    {
        this->_left.setSpeed(-slowest);
        this->_right.setSpeed(fastest);
    }
    else
    {
        this->_left.setSpeed(-fastest);
        this->_right.setSpeed(fastest);
    }
}

void WheelSystem::setSpeeds(float left_speed, float right_speed)
{
    this->_left.setSpeed(-left_speed);
    this->_right.setSpeed(right_speed);
}

void WheelSystem::tourner(float vitesseG, float vitesseD)
{
    this->setSpeeds(vitesseG, vitesseD);
}

void WheelSystem::halt()
{
    this->_left.halt();
    this->_right.halt();
}