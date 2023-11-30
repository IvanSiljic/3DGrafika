#pragma once
#include "geometry.h"

class Material {
public:
    Vec3f diffuseColor;
    float diffuseCoef = 1;
    float speculatCoef = 1;
    float phongExp = 1000;

    Material(): diffuseColor() {};
    explicit Material(const Vec3f &color): diffuseColor(color) {};
};