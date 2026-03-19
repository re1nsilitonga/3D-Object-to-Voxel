#include "geometry.hpp"
#include <limits>

using namespace std;

static void projectTriangle(const Vec3& axis, const Vec3 verts[3], double& outMin, double& outMax) {
    double d0 = axis.dot(verts[0]);
    double d1 = axis.dot(verts[1]);
    double d2 = axis.dot(verts[2]);
    outMin = min({d0, d1, d2});
    outMax = max({d0, d1, d2});
}

static double boxRadius(const Vec3& axis, const Vec3& h) {
    return abs(axis.x) * h.x + abs(axis.y) * h.y + abs(axis.z) * h.z;
}

static bool separated(const Vec3& axis, const Vec3 verts[3], const Vec3& h) {
    double axisLenSq = axis.dot(axis);
    if (axisLenSq < 1e-10) return false; 
    double triMin, triMax;
    projectTriangle(axis, verts, triMin, triMax);
    double r = boxRadius(axis, h);
    return triMin > r || triMax < -r;
}

bool triangleIntersectsBox(const Triangle& tri, const Box& box) {
    Vec3 c = box.center();
    Vec3 h = box.halfSize();
    Vec3 verts[3] = {
        tri.v0 - c,
        tri.v1 - c,
        tri.v2 - c
    };
    Vec3 axisX = {1, 0, 0};
    Vec3 axisY = {0, 1, 0};
    Vec3 axisZ = {0, 0, 1};
    if (separated(axisX, verts, h)) return false;
    if (separated(axisY, verts, h)) return false;
    if (separated(axisZ, verts, h)) return false;
    Vec3 e0 = verts[1] - verts[0];
    Vec3 e1 = verts[2] - verts[1];
    Vec3 e2 = verts[0] - verts[2];
    Vec3 triNormal = e0.cross(e1);
    if (separated(triNormal, verts, h)) return false;
    Vec3 edges[3]  = {e0, e1, e2};
    Vec3 worldAxes[3] = {axisX, axisY, axisZ};\
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Vec3 axis = edges[i].cross(worldAxes[j]);
            if (separated(axis, verts, h)) return false;
        }
    }
    return true;
}

Box computeBoundingBox(const vector<Vec3>& vertices) {
    double inf = numeric_limits<double>::infinity();
    Box box;
    box.min = { inf,  inf,  inf};
    box.max = {-inf, -inf, -inf};
    for (const Vec3& v : vertices) {
        if (v.x < box.min.x) box.min.x = v.x;
        if (v.y < box.min.y) box.min.y = v.y;
        if (v.z < box.min.z) box.min.z = v.z;
        if (v.x > box.max.x) box.max.x = v.x;
        if (v.y > box.max.y) box.max.y = v.y;
        if (v.z > box.max.z) box.max.z = v.z;
    }
    return box;
}

Box transformBoundingBox(const Box& box) {
    Vec3 c = box.center();
    double dx = box.max.x - box.min.x;
    double dy = box.max.y - box.min.y;
    double dz = box.max.z - box.min.z;
    double half = max({dx, dy, dz}) * 0.5;
    half += half * 1e-4;
    Box cubic;
    cubic.min = {c.x - half, c.y - half, c.z - half};
    cubic.max = {c.x + half, c.y + half, c.z + half};
    return cubic;
}