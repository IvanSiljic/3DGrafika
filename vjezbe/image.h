//
// Created by isiljic on 11/3/23.
//
#pragma once
#include "vector"
#include "iostream"
#include "fstream"
#include "algorithm"
#include "geometry.h"

using namespace std;

class Image {
private:
    vector<Vec3f> pixels;
public:
    int width;
    int height;

    Image(int width, int height) : width(width), height(height) {
        pixels = vector<Vec3f>(width * height);
    };

    void setPixel(size_t i, size_t j, const Vec3f color) {
        pixels[(int)i + (int)j*width] = color; // fix i and j iterators
    };

    // save in .ppm format
    void save(const string path) {
        ofstream img;
        img.open(path, ofstream::binary);

        img << "P6\n" << width << " " << height << " " << "\n255\n";

        for (size_t i = 0; i < width * height; i++) {
            for (size_t c = 0; c < 3; c++) {
                char color = (char)(clamp(pixels[i][c], 0.f, 1.f) * 255);
                img << color;
            }
        }

        img.close();
    };
};