#pragma once

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
    void stop();

    /**
     * expects speed between -1 and 1
    */
    void setSpeed(float speed);
};

