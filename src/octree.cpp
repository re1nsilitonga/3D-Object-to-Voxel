#include "octree.hpp"
using namespace std;

bool punyaFace(Face f, vector<Vec3>& v, BoundingBox& b) {
    Vec3 a   = v[f.v1 - 1];
    Vec3 c   = v[f.v2 - 1];
    Vec3 d   = v[f.v3 - 1];
    Vec3 m1  = {(a.x + c.x) / 2, (a.y + c.y) / 2, (a.z + c.z) / 2};
    Vec3 m2  = {(c.x + d.x) / 2, (c.y + d.y) / 2, (c.z + d.z) / 2};
    Vec3 m3  = {(d.x + a.x) / 2, (d.y + a.y) / 2, (d.z + a.z) / 2};
    Vec3 ctr = {(a.x + c.x + d.x) / 3, (a.y + c.y + d.y) / 3, (a.z + c.z + d.z) / 3};

    auto inBox = [&](Vec3 p) {
        return p.x >= b.min.x && p.x <= b.max.x &&
               p.y >= b.min.y && p.y <= b.max.y &&
               p.z >= b.min.z && p.z <= b.max.z;
    };

    return inBox(a) || inBox(c) || inBox(d) || inBox(m1) || inBox(m2) || inBox(m3) || inBox(ctr);
}

void printObjFile(ofstream& out, Vec3 c, float sz, int& vc) {
    float s = sz / 2;
    float x = c.x, y = c.y, z = c.z;
    out << "v " << x-s << " " << y-s << " " << z-s << "\n";
    out << "v " << x+s << " " << y-s << " " << z-s << "\n";
    out << "v " << x+s << " " << y+s << " " << z-s << "\n";
    out << "v " << x-s << " " << y+s << " " << z-s << "\n";
    out << "v " << x-s << " " << y-s << " " << z+s << "\n";
    out << "v " << x+s << " " << y-s << " " << z+s << "\n";
    out << "v " << x+s << " " << y+s << " " << z+s << "\n";
    out << "v " << x-s << " " << y+s << " " << z+s << "\n";
    int i = vc;
    out << "f " << i+1 << " " << i+2 << " " << i+3 << "\n";
    out << "f " << i+1 << " " << i+3 << " " << i+4 << "\n";
    out << "f " << i+5 << " " << i+7 << " " << i+6 << "\n";
    out << "f " << i+5 << " " << i+8 << " " << i+7 << "\n";
    out << "f " << i+1 << " " << i+4 << " " << i+8 << "\n";
    out << "f " << i+1 << " " << i+8 << " " << i+5 << "\n";
    out << "f " << i+2 << " " << i+6 << " " << i+7 << "\n";
    out << "f " << i+2 << " " << i+7 << " " << i+3 << "\n";
    out << "f " << i+1 << " " << i+5 << " " << i+6 << "\n";
    out << "f " << i+1 << " " << i+6 << " " << i+2 << "\n";
    out << "f " << i+4 << " " << i+3 << " " << i+7 << "\n";
    out << "f " << i+4 << " " << i+7 << " " << i+8 << "\n";
    vc += 8;
}

void buildOctree(ofstream& out, BoundingBox& b, vector<Vec3>& v, vector<Face>& f,
                 int d, int md, int& vc, long long& vox, OctreeStats& stats) {
    stats.nodeCount[d]++;

    bool ok = false;
    for (auto& x : f) {
        if (punyaFace(x, v, b)) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        stats.prunedCount[d]++;
        return;
    }

    if (d == md) {
        Vec3 c = {
            (b.min.x + b.max.x) / 2,
            (b.min.y + b.max.y) / 2,
            (b.min.z + b.max.z) / 2
        };
        printObjFile(out, c, (float)(b.max.x - b.min.x), vc);
        vox++;
        return;
    }

    float mx = (b.min.x + b.max.x) / 2;
    float my = (b.min.y + b.max.y) / 2;
    float mz = (b.min.z + b.max.z) / 2;

    for (int i = 0; i < 8; i++) {
        BoundingBox nb;
        nb.min.x = (i & 1) ? mx       : b.min.x;
        nb.max.x = (i & 1) ? b.max.x  : mx;
        nb.min.y = (i & 2) ? my       : b.min.y;
        nb.max.y = (i & 2) ? b.max.y  : my;
        nb.min.z = (i & 4) ? mz       : b.min.z;
        nb.max.z = (i & 4) ? b.max.z  : mz;
        buildOctree(out, nb, v, f, d + 1, md, vc, vox, stats);
    }
}