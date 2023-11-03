//
// Created by isiljic on 11/3/23.
//
#pragma once
#include "geometry.h"

class Ray {
    Vec3f origin;
    Vec3f direction;
public:
    Ray(): origin(Vec3f(0, 0, 0)), direction(Vec3f(0, 0, -1)) {};

    Ray(const Vec3f origin, const Vec3f direction): origin(origin), direction(direction) {};
};
