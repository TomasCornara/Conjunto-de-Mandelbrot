#include <iostream>
#include <cmath>
#include <chrono>
#include "cubo3d.h"


class Renderer3d
{
public:
    Renderer3d(SDL_Window* window, SDL_Renderer* renderer, std::vector<Point3d>& points, std::vector<Vertex>& vertices)
        : renderer(renderer), points(points), vertices(vertices)
    {
        SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);
    }

    void render()
    {
        auto startTime = chrono::high_resolution_clock::now();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
        SDL_RenderClear(renderer);

        std::vector<Point2d> projectedPoints;
        for (const auto& point : points)
        {
            Point3d rotated = rotateY(rotateX(point));
            projectedPoints.push_back(projection(rotated));
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Líneas blancas
        for (const auto& vertex : vertices)
        {
            Point2d start = projectedPoints[vertex.start];
            Point2d end = projectedPoints[vertex.end];
            SDL_RenderLine(renderer,
                           static_cast<int>(start.x), static_cast<int>(start.y),
                           static_cast<int>(end.x), static_cast<int>(end.y));
        }

        SDL_RenderPresent(renderer);

        auto endTime = chrono::high_resolution_clock::now();
        DeltaTime = chrono::duration<float>(endTime - startTime).count();
        rotation += DeltaTime * 50.0f; // Incrementar rotación
    }

private:
    Point3d rotateX(Point3d point)
    {
        float cosAngle = cos(rotation * M_PI / 120.0f);
        float sinAngle = sin(rotation * M_PI / 180.0f);
        return { point.x, point.y * cosAngle - point.z * sinAngle, point.y * sinAngle + point.z * cosAngle };
    }

    Point3d rotateY(Point3d point)
    {
        float cosAngle = cos(rotation * M_PI / 180.0f);
        float sinAngle = sin(rotation * M_PI / 180.0f);
        return { point.x * cosAngle + point.z * sinAngle, point.y, -point.x * sinAngle + point.z * cosAngle };
    }

    Point2d projection(Point3d point)
    {
        float distance = 5.0f;
        float factor = FOV / (distance - point.z);
        return { point.x * factor + WindowSizeX / 2.0f, point.y * factor + WindowSizeY / 2.0f };
    }

    float rotation = 0.0f;
    float FOV = 200.0f;
    float DeltaTime = 0.0f;

    int WindowSizeX;
    int WindowSizeY;

    SDL_Renderer* renderer;
    std::vector<Point3d> points;
    std::vector<Vertex> vertices;
};
