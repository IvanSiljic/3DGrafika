#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void genCircleVer(ofstream & circle, double r, double h, int res) {
    double ang = 360.0 / res;

    for (int i = 0; i < res; i++) {
        double x = r * cos(i * ang * M_PI/180);
        double y = r * sin(i * ang * M_PI/180);

        circle << "v " << x << " " << y << " " << h << endl;
        circle << "v " << x << " " << y << " " << h << endl;
    }
}

void genCircleNorm(ofstream & circle, double r, int res) {
    double ang = 360.0 / res;

    for (int i = 0; i < res; i++) {
        double nx = cos(i * ang * M_PI/180);
        double ny = sin(i * ang * M_PI/180);

        circle << "vn " << nx << " " << ny << " " << 0 << endl;
        circle << "vn " << 0 << " " << 0 << " " << 1 << endl;
    }
}

void genCircleFace(ofstream & circle, int s, int res) {
    for (int i = s; i <= res + s; i++) {
        circle << "f " << s << "//" << s + 1 << " " << i + 1 << "//" << i - s + 3 << " " << i + 2 << "//" << i - s + 4 << endl;
    }
}

void genSideFaces(ofstream & cylinder, int res) {
    for (int i = 1; i <= res; i++) {
        cylinder << "f " << i << "//" << i << " " << i + res << "//" << i << " " << i + res + 1 << "//" << i + 1 << endl;
        cylinder << "f " << i + res + 1 << "//" << i + 1 << " " << i << "//" << i << " " << i << "//" << i + 1 << endl;
    }
}

int main () {
    ofstream cylinder;
    cylinder.open ("cylinder.obj");
    double r = 1;
    double h = 2;
    int res = 36;

    genCircleVer(cylinder, r, -h/2, res);
    genCircleVer(cylinder, r, h/2, res);

    genCircleNorm(cylinder, r, res);

    genCircleFace(cylinder, 1, res);
    genCircleFace(cylinder, 37, res);

    genSideFaces(cylinder, res);

    cylinder.close();
    return 0;
}