#pragma once
#include "objects.h"
#include <vector>
#include "light.h"

using namespace std;

class Scene {
    vector<Object*> objects;
    vector<Light*> lights;

    bool sceneIntersect(const Ray &ray, Vec3f &hitPoint, Vec3f &hitNormal, Object* &hitObject) const {
        Vec3f normal;
        float best_t = numeric_limits<float>::max();
        float t = -1;
        bool didIntersect = false;

        for (auto obj : objects) {
            if (obj->rayIntersect(ray, t, normal)) {
                if (t < best_t && t > 0) {
                    best_t = t;
                    hitPoint = ray.origin + ray.direction * t;
                    hitObject = obj;
                    hitNormal = normal;
                    didIntersect = true;
                }
            }
        }

        return didIntersect;
    }

    bool isLightObscured(const Light* light, Vec3f hitPoint) const {
        Vec3f lightDirection = (light->position - hitPoint).normalize();
        Vec3f lightOrigin = hitPoint + lightDirection * 0.001;
        Ray lightRay(lightOrigin, lightDirection);

        Vec3f recHitPoint;
        Vec3f recHitNormal;
        Object *recHitObject;

        if (!sceneIntersect(lightRay, recHitPoint, recHitNormal, recHitObject))
            return false;

        float lightDist = (light->position - hitPoint).norm();
        float hitDist = (recHitPoint - hitPoint).norm();

        if (hitDist >= lightDist)
            return false;

        return true;
    }

    void processLights(const Vec3f  hitPoint, const Vec3f hitNormal, const Object* hitObject, const Ray ray, float &diff, float &spec) const {
        for (auto light : lights) {
            if (isLightObscured(light, hitPoint))
                continue;

            Vec3f l = (light->position - hitPoint).normalize();
            float r = (light->position - hitPoint).norm();

            float kD = hitObject->material.diffuseCoef;
            float distFactor = light->intensity / (r * r);
            float angle = hitNormal * l;
            float L = kD * distFactor * max(0.f, angle);

            diff += L;

            Vec3f h = (-ray.direction + l).normalize();
            float kS = hitObject->material.speculatCoef;
            float p = hitObject->material.phongExp;

            L = kS * distFactor * pow(max(0.f, hitNormal * h), p);

            spec += L;
        }
    }

public:
    Vec3f castRay(const Ray &ray) const {
        Vec3f hitPoint;
        Vec3f hitNormal;
        Object* hitObject;

        if (sceneIntersect(ray, hitPoint, hitNormal, hitObject)) {
            float diff = 0;
            float spec = 0;

            processLights(hitPoint, hitNormal, hitObject, ray, diff, spec);

            return hitObject->material.diffuseColor * diff + Vec3f(1, 1, 1) * spec;
        }
        
        return {0, 0, 0};
    }

    void addObject(Object * object) {
        objects.push_back(object);
    }

    void addLight(Light *light) {
        lights.push_back(light);
    }
};