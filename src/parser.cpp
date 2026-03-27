#include "parser.hpp"
#include <iostream>
using namespace std;

static bool parseFaceIndex(const string& token, int& outIndex) {
    size_t slashPos = token.find('/');
    string idx = (slashPos == string::npos) ? token : token.substr(0, slashPos);
    if (idx.empty()) return false;
    size_t processed = 0;
    int value = 0;
    try {
        value = stoi(idx, &processed);
    } catch (...) {
        return false;
    }
    if (processed != idx.size()) return false;
    if (value <= 0) return false;
    outIndex = value;
    return true;
}

bool loadOBJRoot(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces, Box& root) {
    vertices.clear();
    faces.clear();
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: tidak dapat membuka file '" << filePath << "'\n";
        return false;
    }
    string line;
    int lineNo = 0;
    root = {{1e9, 1e9, 1e9}, {-1e9, -1e9, -1e9}};
    while (getline(file, line)) {
        lineNo++;
        stringstream ss(line);
        string type;
        ss >> type;
        if (type == "v") {
            Vec3 v;
            if (!(ss >> v.x >> v.y >> v.z)) {
                cerr << "Error: format vertex tidak valid pada baris " << lineNo << "\n";
                return false;
            }
            vertices.push_back(v);
            root.min.x = min(root.min.x, v.x); root.max.x = max(root.max.x, v.x);
            root.min.y = min(root.min.y, v.y); root.max.y = max(root.max.y, v.y);
            root.min.z = min(root.min.z, v.z); root.max.z = max(root.max.z, v.z);
        } else if (type == "f") {
            string t1, t2, t3, t4;
            ss >> t1 >> t2 >> t3;
            if (t1.empty() || t2.empty() || t3.empty()) {
                cerr << "Error: face harus terdiri dari 3 vertex pada baris " << lineNo << "\n";
                return false;
            }
            if (ss >> t4) {
                cerr << "Error: face non-segitiga terdeteksi pada baris " << lineNo << "\n";
                return false;
            }
            Face f;
            if (!parseFaceIndex(t1, f.v1) || !parseFaceIndex(t2, f.v2) || !parseFaceIndex(t3, f.v3)) {
                cerr << "Error: indeks face tidak valid pada baris " << lineNo << "\n";
                return false;
            }
            faces.push_back(f);
        }
    }
    if (vertices.empty()) {
        cerr << "Error: tidak ada vertex ditemukan di file\n";
        return false;
    }
    if (faces.empty()) {
        cerr << "Error: tidak ada face ditemukan di file\n";
        return false;
    }

    int vertexCount = (int)vertices.size();
    for (const Face& f : faces) {
        if (f.v1 > vertexCount || f.v2 > vertexCount || f.v3 > vertexCount) {
            cerr << "Error: indeks face melebihi jumlah vertex\n";
            return false;
        }
    }

    return true;
}

bool loadOBJ(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces) {
    Box root;
    return loadOBJRoot(filePath, vertices, faces, root);
}

string generateOutputPath(const string& inputPath) {
    size_t dotPos = inputPath.rfind('.');
    size_t sepPos = inputPath.find_last_of("/\\");
    bool hasDot      = dotPos != string::npos;
    bool dotAfterSep = hasDot && (sepPos == string::npos || dotPos > sepPos);
    string base = dotAfterSep ? inputPath.substr(0, dotPos) : inputPath;
    return base + "-voxelized.obj";
}