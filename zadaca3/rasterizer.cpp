#include <iostream>
#include <cmath>
#include <cfloat>
#include "tgaimage.h"
#include "vector"

using namespace std;

typedef pair<int, int> Point2D;
typedef tuple<float, float, float> Point3D;
typedef pair<float, float> Vec2f;

void set_color(int x, int y, TGAImage &image, TGAColor color, bool invert = false)
{
    image.set(y, x, color);
}

float line(float x0, float y0, float x1, float y1, float x, float y)
{
    return (y0 - y1) * x + (x1 - x0) * y + x0 * y1 - x1 * y0;
}

void line_naive(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    for (float t = 0; t < 1; t += 0.01)
    {
        int x = x0 * (1.0f - t) + x1 * t;
        int y = x0 * (1.0f - t) + y1 * t;
        set_color(x, y, image, color);
    }
}

void line_midpoint(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color, bool invert)
{
    int y = y0;
    int d = line(x0, y0, x1, y1, x0 + 1, y0 + 0.5);

    int dx = (x1 - x0);
    int dy = (y1 - y0);
    int increment = 1;

    if (dy < 0)
    {
        // pravac ide od gore prema dolje
        dy = -dy;
        increment = -increment;
    }

    for (int x = x0; x <= x1; ++x)
    {
        if (invert)
        {
            set_color(x, y, image, color);
        }
        else
        {
            set_color(y, x, image, color);
        }

        if (d < 0)
        {
            y = y + increment;
            d = d + dx - dy;
        }
        else
        {
            d = d - dy;
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    // 'transponiraj' duzinu ako je veci od 1
    bool invert = false;
    if (abs(x1 - x0) < abs(y1 - y0))
    {
        swap(x0, y0);
        swap(x1, y1);
        invert = true;
    }

    // zamijeni tocke ako pravac ide s desna na lijevo
    if (x1 < x0)
    {
        swap(x0, x1);
        swap(y0, y1);
    }

    // nacrtaj duzinu
    line_midpoint(x0, y0, x1, y1, image, color, invert);
}

void draw_triangle_2d(Point2D t1, Point2D t2, Point2D t3, TGAColor color, TGAImage &image);

void draw_triangle_2d_gouraud(Point2D t1, Point2D t2, Point2D t3, TGAColor c1, TGAColor c2, TGAColor c3, TGAImage &image);

void draw_triangle(Point3D p1, Point3D p2, Point3D p3, TGAColor color, TGAImage &image);

void draw_triangle_tex(Point3D p1, Point3D p2, Point3D p3, Vec2f u1, Vec2f u2, Vec2f u3, const char * tex, TGAImage &image);

void draw_triangle_tex_corrected(Point3D p1, Point3D p2, Point3D p3, Vec2f u1, Vec2f u2, Vec2f u3, const char * tex, TGAImage &image);

// dimenzije slike
const int width  = 512;
const int height = 512;

const float cameraDist = 1.0;

// definirajmo boje
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);
const TGAColor blue  = TGAColor(0, 0, 255, 255);
const TGAColor green  = TGAColor(0, 255, 0, 255);


int main()
{
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);

    Point3D t1{-48, -10, 82};
    Point3D t2{29, -15, 44};
    Point3D t3{13, 34, 114};
    Vec2f u1{0, 0};
    Vec2f u2{0, 1};
    Vec2f u3{1, 0};

    draw_triangle_tex_corrected(t1, t2, t3, u1, u2, u3, "assets/wall.tga", image);

    // spremi sliku
    image.flip_vertically();
    image.write_tga_file("image.tga");
}

float distFromLine(Point2D a, Point2D b, Point2D t) {
    return (float)((a.second - b.second)*t.first + (b.first - a.first)*t.second + a.first*b.second - b.first*a.second);
}

void draw_triangle_2d(Point2D t1, Point2D t2, Point2D t3, TGAColor color, TGAImage &image) {
    int xMin, yMin, xMax, yMax;

    xMin = min(t1.first, min(t2.first, t3.first));
    yMin = min(t1.second, min(t2.second, t3.second));

    xMax = max(t1.first, max(t2.first, t3.first));
    yMax = max(t1.second, max(t2.second, t3.second));

    for (int i = xMin; i <= xMax; i++){
        for (int j = yMin; j <= yMax; j++) {
            float L = distFromLine(t2, t3, Point2D{i, j}) / distFromLine(t2, t3, t1);
            float B = distFromLine(t1, t3, Point2D{i, j}) / distFromLine(t1, t3, t2);
            float G = distFromLine(t1, t2, Point2D{i, j}) / distFromLine(t1, t2, t3);

            if (L >= 0 && L <= 1 && B >= 0 && B <= 1 && G >= 0 && G <= 1) {
                if ((L > 0 || distFromLine(t2, t3, t1) * distFromLine(t2, t3, Point2D{-1, -1}) >= 0) &&
                    (B > 0 || distFromLine(t1, t3, t2) * distFromLine(t1, t3, Point2D{-1, -1}) >= 0) &&
                    (G > 0 || distFromLine(t1, t2, t3) * distFromLine(t1, t2, Point2D{-1, -1}) >= 0)) {

                    image.set(i, j, color);
                }
            }
        }
    }
}

void draw_triangle_2d_gouraud(Point2D t1, Point2D t2, Point2D t3, TGAColor c1, TGAColor c2, TGAColor c3, TGAImage &image) {
    int xMin, yMin, xMax, yMax;

    xMin = min(t1.first, min(t2.first, t3.first));
    yMin = min(t1.second, min(t2.second, t3.second));

    xMax = max(t1.first, max(t2.first, t3.first));
    yMax = max(t1.second, max(t2.second, t3.second));

    for (int i = xMin; i <= xMax; i++){
        for (int j = yMin; j <= yMax; j++) {
            float L = distFromLine(t2, t3, Point2D{i, j}) / distFromLine(t2, t3, t1);
            float B = distFromLine(t1, t3, Point2D{i, j}) / distFromLine(t1, t3, t2);
            float G = distFromLine(t1, t2, Point2D{i, j}) / distFromLine(t1, t2, t3);

            if (L >= 0 && L <= 1 && B >= 0 && B <= 1 && G >= 0 && G <= 1) {
                if ((L > 0 || distFromLine(t2, t3, t1) * distFromLine(t2, t3, Point2D{-1, -1}) >= 0) &&
                    (B > 0 || distFromLine(t1, t3, t2) * distFromLine(t1, t3, Point2D{-1, -1}) >= 0) &&
                    (G > 0 || distFromLine(t1, t2, t3) * distFromLine(t1, t2, Point2D{-1, -1}) >= 0)) {

                    TGAColor color{(L * c1.r + B * c2.r + G * c3.r), (L * c1.g + B * c2.g + G * c3.g),
                                   (L * c1.b + B * c2.b + G * c3.b), (L * c1.a + B * c2.a + G * c3.a)};

                    image.set(i, j, color);
                }
            }
        }
    }
}

void draw_triangle(Point3D p1, Point3D p2, Point3D p3, TGAColor color, TGAImage &image) {
    float adjustX = (float)width/2;
    float adjustY = (float)height/2;

    Point2D t1{((cameraDist/get<2>(p1)) * get<0>(p1)) * adjustX + adjustX, ((cameraDist / get<2>(p1)) * get<1>(p1)) * adjustY + adjustY};
    Point2D t2{((cameraDist/get<2>(p2)) * get<0>(p2)) * adjustX + adjustX, ((cameraDist / get<2>(p2)) * get<1>(p2)) * adjustY + adjustY};
    Point2D t3{((cameraDist/get<2>(p3)) * get<0>(p3)) * adjustX + adjustX, ((cameraDist / get<2>(p3)) * get<1>(p3)) * adjustY + adjustY};

    int xMin, yMin, xMax, yMax;

    xMin = min(t1.first, min(t2.first, t3.first));
    yMin = min(t1.second, min(t2.second, t3.second));

    xMax = max(t1.first, max(t2.first, t3.first));
    yMax = max(t1.second, max(t2.second, t3.second));

    for (int i = xMin; i <= xMax; i++){
        for (int j = yMin; j <= yMax; j++) {
            float L = distFromLine(t2, t3, Point2D{i, j}) / distFromLine(t2, t3, t1);
            float B = distFromLine(t1, t3, Point2D{i, j}) / distFromLine(t1, t3, t2);
            float G = distFromLine(t1, t2, Point2D{i, j}) / distFromLine(t1, t2, t3);

            if (L >= 0 && L <= 1 && B >= 0 && B <= 1 && G >= 0 && G <= 1) {
                image.set(i, j, color);
            }
        }
    }
}

void draw_triangle_tex(Point3D p1, Point3D p2, Point3D p3, Vec2f u1, Vec2f u2, Vec2f u3, const char * tex, TGAImage &image) {
    float adjustX = (float)width/2;
    float adjustY = (float)height/2;

    Point2D t1{((cameraDist/get<2>(p1)) * get<0>(p1)) * adjustX + adjustX, ((cameraDist / get<2>(p1)) * get<1>(p1)) * adjustY + adjustY};
    Point2D t2{((cameraDist/get<2>(p2)) * get<0>(p2)) * adjustX + adjustX, ((cameraDist / get<2>(p2)) * get<1>(p2)) * adjustY + adjustY};
    Point2D t3{((cameraDist/get<2>(p3)) * get<0>(p3)) * adjustX + adjustX, ((cameraDist / get<2>(p3)) * get<1>(p3)) * adjustY + adjustY};

    TGAImage texture;

    if(!texture.read_tga_file(tex)){
        return;
    }

    int xMin, yMin, xMax, yMax;

    xMin = min(t1.first, min(t2.first, t3.first));
    yMin = min(t1.second, min(t2.second, t3.second));

    xMax = max(t1.first, max(t2.first, t3.first));
    yMax = max(t1.second, max(t2.second, t3.second));

    for (int i = xMin; i <= xMax; i++){
        for (int j = yMin; j <= yMax; j++) {
            float L = distFromLine(t2, t3, Point2D{i, j}) / distFromLine(t2, t3, t1);
            float B = distFromLine(t1, t3, Point2D{i, j}) / distFromLine(t1, t3, t2);
            float G = distFromLine(t1, t2, Point2D{i, j}) / distFromLine(t1, t2, t3);

            if (L >= 0 && L <= 1 && B >= 0 && B <= 1 && G >= 0 && G <= 1) {
                Point2D texCoord{(int)((L * u1.first + B * u2.first + G * u3.first) * texture.get_width()), (int)((L * u1.second + B * u2.second + G * u3.second)* texture.get_height())};

                image.set(i, j, texture.get(texCoord.first, texCoord.second));
            }
        }
    }
}

void draw_triangle_tex_corrected(Point3D p1, Point3D p2, Point3D p3, Vec2f u1, Vec2f u2, Vec2f u3, const char * tex, TGAImage &image) {
    TGAImage texture;

    if(!texture.read_tga_file(tex)){
        return;
    }

    int texWidth = image.get_width();
    int texHeight = image.get_height();

    u1.first *= (float)texWidth;
    u2.first *= (float)texWidth;
    u3.first *= (float)texWidth;
    u1.second *= (float)texHeight;
    u2.second *= (float)texHeight;
    u3.second *= (float)texHeight;

    float adjustX = (float)width/2;
    float adjustY = (float)height/2;

    get<0>(p1) = (cameraDist/get<2>(p1)) * get<0>(p1) * adjustX + adjustX;
    get<1>(p1) = ((cameraDist / get<2>(p1)) * get<1>(p1)) * adjustY + adjustY;
    get<0>(p2) = ((cameraDist/get<2>(p2)) * get<0>(p2)) * adjustX + adjustX;
    get<1>(p2) = ((cameraDist / get<2>(p2)) * get<1>(p2)) * adjustY + adjustY;
    get<0>(p3) = ((cameraDist/get<2>(p3)) * get<0>(p3)) * adjustX + adjustX;
    get<1>(p3) = ((cameraDist / get<2>(p3)) * get<1>(p3)) * adjustY + adjustY;

    int xMin, yMin, xMax, yMax;

    xMin = (int)min(get<0>(p1), min(get<0>(p2) , get<0>(p3)));
    yMin = (int)min(get<1>(p1), min(get<1>(p2), get<1>(p3)));

    xMax = (int)max(get<0>(p1), max(get<0>(p2) , get<0>(p3)));
    yMax = (int)max(get<1>(p1), max(get<0>(p2) , get<0>(p3)));

    for (int i = xMin; i <= xMax; i++){
        for (int j = yMin; j <= yMax; j++) {
            float L = distFromLine(Point2D{get<0>(p2), get<1>(p2)}, Point2D{get<0>(p3), get<1>(p3)}, Point2D{i, j}) / distFromLine(Point2D{get<0>(p2), get<1>(p2)}, Point2D{get<0>(p3), get<1>(p3)}, Point2D{get<0>(p1), get<1>(p1)});
            float B = distFromLine(Point2D{get<0>(p1), get<1>(p1)}, Point2D{get<0>(p3), get<1>(p3)}, Point2D{i, j}) / distFromLine(Point2D{get<0>(p1), get<1>(p1)}, Point2D{get<0>(p3), get<1>(p3)}, Point2D{get<0>(p2), get<1>(p2)});
            float G = distFromLine(Point2D{get<0>(p1), get<1>(p1)}, Point2D{get<0>(p2), get<1>(p2)}, Point2D{i, j}) / distFromLine(Point2D{get<0>(p1), get<1>(p1)}, Point2D{get<0>(p2), get<1>(p2)}, Point2D{get<0>(p3), get<1>(p3)});

            if (L >= 0 && L <= 1 && B >= 0 && B <= 1 && G >= 0 && G <= 1) {
                float w = 1.0f / (L/get<2>(p1) + B / get<2>(p2) + G / get<2>(p3));

                float u0 = L * u1.first / get<2>(p1);
                float v0 = L * u1.second / get<2>(p1);
                float u1 = B * u2.first / get<2>(p2);
                float v1 = B * u2.second / get<2>(p2);
                float u2 = G * u3.first / get<2>(p3);
                float v2 = G * u3.second / get<2>(p3);

                Point2D texCoord{w * (float)(u0 + u1 + u2), w * (float)(v0 + v1 + v2)};

                image.set(i, j, texture.get(texCoord.first, texCoord.second));
            }
        }
    }
}
