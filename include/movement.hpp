#pragma once
#include "math.hpp"

class Motor
{
private:
    int _speed_pin;
    int _clockwise_pin;
    int _counter_clockwise_pin;
    float _calibration;
    void setClockwise();
    void setCounterClockwise();

public:
    Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin);
    Motor(int speed_pin, int clockwise_pin, int counter_clockwise_pin, float calibration);
    void begin();
    void halt();

    /**
     * expects speed between -1 and 1
     */
    virtual void setSpeed(float speed);
    /**
     * will automatically rectify to a number between 0 and 1
    */
    void setCalibration(float calibration);
    float getCalibration();
};

// TODO: TRY TO MAKE THAT WORK?
// class InvertedMotor: public Motor {
//     public:
//         void setSpeed(float speed) override;
// };

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