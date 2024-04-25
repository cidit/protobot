#pragma once
#include "sensor.hpp"

class Bumper: Sensor<bool> {
    Bumper();
    void begin() override;
};
bool detectObstacle();