#include <Arduino.h>
#include "math.hpp"

Vector normalize(const Vector v)
{
    auto magnitude = sqrtf(sq(v.x) + sq(v.y));

    return {
        v.x / magnitude,
        v.y / magnitude,
    };
}

Vector add(const Vector v1, const Vector v2)
{
    return {
        v1.x + v2.x,
        v1.y + v2.y,
    };
}

Vector neg(const Vector v)
{
    return {
        -v.x,
        -v.y,
    };
}