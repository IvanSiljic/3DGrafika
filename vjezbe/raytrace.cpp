#include "geometry.h"
#include "image.h"
#include "ray.h"
#include "objects.h"
#include "scene.h"
#include "material.h"

using namespace std;

Ray rayToPixel(Vec3f origin, const Image &img, int i, int j) {
    Ray ray = Ray();

    float aspectRatio = (float)img.width / img.height;

    float x = (float)(-1 + 2 * (i + 0.5) / (float)img.width) * aspectRatio;
    float y = (float)(1 - 2 * (j + 0.5) / (float)img.height);
    float z = -1;

    ray.origin = origin;
    ray.direction = Vec3f(x, y, z).normalize();
    return ray;
}

void render(const Scene &scene) {
    int width = 1024;
    int height = 768;

    Vec3f origin{0, 0 ,0};

    Image img = Image(width, height);

    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            Ray ray = rayToPixel(origin, img, (int)i, (int)j);
            Vec3f color = scene.castRay(ray);
            img.setPixel(i, j, color);
        }
    }

    img.save("./image.ppm");
}

int main() {
    Scene scene;

    Material red(Vec3f(1, 0, 0));
    Material green(Vec3f(0, 1, 0));
    Material blue(Vec3f(0, 0, 1));
    Material grey(Vec3f(0.5, 0.5, 0.5));

    Sphere s1(Vec3f(-3, 0, -16), 2, red);
    Sphere s2(Vec3f(-1, -1.5, -12), 2, green);
    Sphere s3(Vec3f(1.5, -0.5, -18), 3, blue);
    Sphere s4(Vec3f(7, 5, -18), 4, grey);

    scene.addObject(&s1);
    scene.addObject(&s2);
    scene.addObject(&s3);
    scene.addObject(&s4);

    Light l1(Vec3f(-20, 20, 20), 1500);
    Light l2(Vec3f(20, 30, 20), 1500);

    scene.addLight(&l1);
    scene.addLight(&l2);

    render(scene);
    return 0;
}