#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Vec3 {
    double x, y, z;

    Vec3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(double s)      const { return {x * s,   y * s,   z * s};   }

    double dot(const Vec3& o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    Vec3 cross(const Vec3& o) const {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }
};

struct Box {
    Vec3 min, max;

    Vec3 center() const {
        return {
            (min.x + max.x) * 0.5,
            (min.y + max.y) * 0.5,
            (min.z + max.z) * 0.5
        };
    }

    Vec3 halfSize() const {
        return {
            (max.x - min.x) * 0.5,
            (max.y - min.y) * 0.5,
            (max.z - min.z) * 0.5
        };
    }
};

using BoundingBox = Box;

struct Triangle {
    Vec3 v0, v1, v2;
};

struct Face {
    int v1, v2, v3;
};

bool triangleIntersectsBox(const Triangle& tri, const Box& box);

Box computeBoundingBox(const vector<Vec3>& vertices);
Box transformBoundingBox(const Box& box);