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
    Sphere(Vec3f c, float r): r(r), c(c) {};

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

class Cuboid : public Object {
    Vec3f min;
    Vec3f max;

public:
    Cuboid(const Vec3f min, const Vec3f max, const Material mat)
            : min{min}, max{max} {
        Object::material = mat;
    }

    bool rayIntersect(const Ray &ray, float &t, Vec3f &normal) const {
        float tNear = -INFINITY;
        float tFar = INFINITY;

        for (int i = 0; i < 3; i++) {
            if (ray.direction[i] == 0) {
                if (ray.origin[i] < min[i] || ray.origin[i] > max[i])
                    return false;
            } else {
                float t1 = (min[i] - ray.origin[i]) / ray.direction[i];
                float t2 = (max[i] - ray.origin[i]) / ray.direction[i];

                if (t1 > t2)
                    swap(t1, t2);

                tNear = tNear > t1 ? tNear : t1;
                tFar = tFar < t2 ? tFar : t2;

                if (tNear > tFar)
                    return false;

                if (tFar < 0)
                    return false;
            }
        }

        t = tNear;

        Vec3f hitPoint = ray.origin + ray.direction * t;

        for (int i = 0; i < 3; i++) {
            if (hitPoint[i] >= max[i]) {
                normal = Vec3f(i == 0, i == 1, i == 2);
                break;
            }
            if (hitPoint[i] <= min[i]) {
                normal = Vec3f(i == 0, i == 1, i == 2);
                break;
            }
        }

        return true;
    }
};
