#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <bits/stdc++.h>
#include "geometry.hpp"
using namespace std;

struct OctreeStats {
    vector<int> nodeCount;
    vector<int> prunedCount;
    int maxDepth;

    OctreeStats() : maxDepth(0) {}

    void init(int depth) {
        maxDepth = depth;
        nodeCount.assign(depth + 2, 0);
        prunedCount.assign(depth + 2, 0);
    }
};

bool punyaFace(Face f, vector<Vec3>& v, BoundingBox& b);

void printObjFile(ofstream& out, Vec3 c, float sz, int& vc);

void buildOctree(ofstream& out, BoundingBox& b, vector<Vec3>& v, vector<Face>& f,
                 int d, int md, int& vc, long long& vox, OctreeStats& stats);

#endif