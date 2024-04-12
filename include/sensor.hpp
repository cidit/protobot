#pragma once

template <typename Measure>
class Sensor
{
protected:
    virtual void begin() = 0;
    virtual bool sample(Measure &out) = 0;
};
