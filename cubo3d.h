#ifndef CUBO3D_H_INCLUDED
#define CUBO3D_H_INCLUDED
#include <vector>


#include <SDL3/SDL.h>

using namespace std;

struct Point2d
{
    float x;
    float y;
};

struct Point3d
{
    float x;
    float y;
    float z;
};

struct Vertex
{
    int start;
    int end;
};

// Cubo
std::vector<Point3d> points
{
    Point3d{ -1.0f, -1.0f, -1.0f }, Point3d{ 1.0f, -1.0f, -1.0f },
    Point3d{ -1.0f,  1.0f, -1.0f }, Point3d{ 1.0f,  1.0f, -1.0f },
    Point3d{ -1.0f, -1.0f,  1.0f }, Point3d{ 1.0f, -1.0f,  1.0f },
    Point3d{ -1.0f,  1.0f,  1.0f }, Point3d{ 1.0f,  1.0f,  1.0f }
};

std::vector<Vertex> vertices
{
    Vertex{ 0, 1 }, Vertex{ 1, 3 }, Vertex{ 3, 2 }, Vertex{ 2, 0 }, // Cara frontal
    Vertex{ 4, 5 }, Vertex{ 5, 7 }, Vertex{ 7, 6 }, Vertex{ 6, 4 }, // Cara trasera
    Vertex{ 0, 4 }, Vertex{ 1, 5 }, Vertex{ 2, 6 }, Vertex{ 3, 7 }  // Conexiones entre caras
};



#endif // CUBO3D_H_INCLUDED
