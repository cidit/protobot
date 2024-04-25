#pragma once
#include "math.hpp"
#include "motor.hpp"

class WheelSystem
{
private:
    Motor _left;
    Motor _right;

public:
    WheelSystem(Motor left, Motor right);
    void begin();
    void setMovement(Vector movement);
    void setSpeeds(float left_speed, float right_speed);
    /**
     * remplis devis
    */
    void tourner(float vitesseG, float vitesseD);
    void halt();
};