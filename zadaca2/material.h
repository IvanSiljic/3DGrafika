#pragma once
#include "geometry.h"

class Material {
public:
    Vec3f diffuseColor;
    float diffuseCoef = 1;
    float speculatCoef = 1;
    float reflCoef = 0;
    float opacityCoef = 0;
    float phongExp = 1000;

    Material(): diffuseColor(1, 1, 1) {};
    explicit Material(const Vec3f &color): diffuseColor(color) {};
    explicit Material(const Vec3f &color, float reflCoef, float opacityCoef): diffuseColor(color), reflCoef(reflCoef), opacityCoef(opacityCoef) {};
};