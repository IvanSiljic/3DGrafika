#pragma once
#include "cmath"
#include "geometry.h"
#include "ray.h"
#include "material.h"

class Object {
public:
    Material material;
    virtual bool rayIntersect(const Ray &ray, float &t, Vec3f &normal) const = 0;
};

class Sphere : public Object {
    float r;
    Vec3f c;

public:
    Sphere(Vec3f &c, float &r): r(r), c(c) {};

    Sphere(Vec3f c, float r, Material mat): r(r), c(c) {
        Object::material = mat;
    };

    bool rayIntersect(const Ray &ray, float &t, Vec3f &normal) const {
        Vec3f eMinusC = ray.origin - c;
        float d2 = ray.direction * ray.direction;

        float disc = pow(ray.direction * eMinusC, 2) - d2 * (eMinusC * eMinusC - r * r);

        if (disc < 0)
            return false;

        bool rayInsideSphere = eMinusC * eMinusC <= r * r;
        if (rayInsideSphere) {
            float t1 = (-ray.direction * eMinusC + sqrt(disc)) / d2;
            t = t1;
        } else {
            float t2 = (-ray.direction * eMinusC - sqrt(disc)) / d2;
            t = t2;
        }

        Vec3f hitPoint = ray.origin + ray.direction * t;
        normal = (hitPoint - c).normalize();

        return true;
    }
};
