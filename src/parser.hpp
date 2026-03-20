#pragma once
#include <bits/stdc++.h>
#include "geometry.hpp"

using namespace std;

struct Face {
	int v1, v2, v3;
};

bool loadOBJRoot(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces, Box& root);
bool loadOBJ(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces);
