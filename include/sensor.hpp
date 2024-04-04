template <typename Measure>
class Sensor
{
    virtual Measure sample() = 0;
};

using Distance = int;
class Ultrasound : Sensor<Distance>
{
private:
    int _pin;

public:
    Ultrasound(int pin);
    Distance sample() override;
};