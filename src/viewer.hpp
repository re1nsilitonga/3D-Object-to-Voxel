#pragma once

#include <SFML/Graphics.hpp>
#include "geometry.hpp"

using namespace std;

struct FaceToDraw {
    sf::Vertex v[3];
    float zDepth;
};

Vec3 rotateX(const Vec3& p, double a);
Vec3 rotateY(const Vec3& p, double a);
sf::Vector2f project(const Vec3& p, double scale, int w, int h);
