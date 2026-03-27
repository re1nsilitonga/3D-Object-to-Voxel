#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "geometry.hpp"
using namespace std;

bool loadOBJRoot(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces, Box& root);

bool loadOBJ(const string& filePath, vector<Vec3>& vertices, vector<Face>& faces);

string generateOutputPath(const string& inputPath);