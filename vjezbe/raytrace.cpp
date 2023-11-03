//
// Created by isiljic on 11/3/23.
//
#include "geometry.h"
#include "image.h"
#include "ray.h"

using namespace std;

Ray rayToPixel(const Vec3f origin, const Image &img, int i, int j) {
    float u = (float)(-1 + 2*(i + 0.5)) / (float)img.width;
    float v = (float)(-1 + 2*(j + 0.5)) / (float)img.height;
    float w = -1;

    Vec3f direction = Vec3f{u, v, w}.normalize();

    Ray ray = Ray(origin, direction);

    return ray;
}

void render() {
    int width = 1024;
    int height = 768;

    Image img = Image(width, height);

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            Vec3f color{(float)j / height, (float)j / height, (float)j / height};
            img.setPixel(i, j, color);
        }
    }

    img.save("./image.ppm");
}

int main() {
    render();
    return 0;
}