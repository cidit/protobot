#pragma once
#include <Arduino.h>

struct Vector
{
    float x, y;
};

Vector normalize(const Vector v);
Vector add(const Vector v1, const Vector v2);
Vector neg(const Vector v);