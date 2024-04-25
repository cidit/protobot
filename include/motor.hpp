#pragma once

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