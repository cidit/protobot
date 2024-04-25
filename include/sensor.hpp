#pragma once

template <typename Measure>
class Sensor
{
protected:
    Measure last;
    virtual void begin() = 0;
    virtual bool sample(Measure &out) = 0;
    virtual Measure getLast() {
        return this->last;
    }
    virtual void poll() {
        Measure measure;
        auto success = sample(measure);
        if (success) {
            last = measure;
        }
    }
};
