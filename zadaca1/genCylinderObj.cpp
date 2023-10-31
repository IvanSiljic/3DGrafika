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
    }

    for (int i = 0; i < res; i++) {
        double x = r * cos(i * ang * M_PI/180);
        double y = r * sin(i * ang * M_PI/180);

        circle << "v " << x << " " << y << " " << h << endl;
    }
}

void genCircleNorm(ofstream & circle, double r, int res) {
    double ang = 360.0 / res;

    for (int i = 0; i < res; i++) {
        circle << "vn " << 0 << " " << 0 << " " << 1 << endl;
    }

    for (int i = 0; i < res; i++) {
        double nx = cos(i * ang * M_PI/180);
        double ny = sin(i * ang * M_PI/180);

        circle << "vn " << nx << " " << ny << " " << 0 << endl;
    }
}

void genCircleFace(ofstream & circle, int s, int res) {
    for (int i = s; i < res + s - 2; i++) {
        circle << "f " << s << "//" << s << " " << i + 1 << "//" << i + 1 << " " << i + 2 << "//" << i + 2 << endl;
    }
}

void genSideFaces(ofstream & cylinder, int res) {
    for (int i = 1; i < res; i++) {
        int n1 = i + res + res/2 + 1;
        int n2 = i + res*3 + res/2;
        int n3 = i + res*3 + res/2 + 1;
        if (n1 > res*2) {
            n1 -= res;
        }
        if (n2 > res*4) {
            n2 -= res;
        }
        if (n3 > res*4) {
            n3 -= res;
        }
        cylinder << "f " << i + res + 1 << "//" << n1 << " " << i + res*3 << "//" << n2 << " " << i + res*3 + 1 << "//" << n3 << endl; // this doesn't work properly
        cylinder << "f " << i + res*3 << "//" << i + res*3 << " " << i + res << "//" << i + res << " " << i + res + 1 << "//" << i + res + 1 << endl;
    }
    cylinder << "f " << res + 1 << "//" << res + 1 << " " << res*3 + 1 << "//" << res*3 + 1 << " " << res*4 << "//" << res*4 << endl;
    cylinder << "f " << res*4 << "//" << res*4 - res/2<< " " << res + 1 << "//" << res + res/2 + 1 << " " << res*2 << "//" << res*2 - res/2 << endl;

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
    genCircleNorm(cylinder, r, res);


    genCircleFace(cylinder, 1, res);
    genCircleFace(cylinder, res*2 + 1, res);

    genSideFaces(cylinder, res);

    cylinder.close();
    return 0;
}