#include "viewer.hpp"
#include "parser.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Vec3 rotateX(const Vec3& p, double a) {
    double c = cos(a), s = sin(a);
    return {p.x, p.y * c - p.z * s, p.y * s + p.z * c};
}

Vec3 rotateY(const Vec3& p, double a) {
    double c = cos(a), s = sin(a);
    return {p.x * c - p.z * s, p.y, p.x * s + p.z * c};
}

sf::Vector2f project(const Vec3& p, double scale, int w, int h) {
    return {
        static_cast<float>(w * 0.5 + p.x * scale),
        static_cast<float>(h * 0.5 - p.y * scale)
    };
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Penggunaan: " << argv[0] << " <file-obj>\n";
        return 1;
    }

    string path = argv[1];
    {
        ifstream f(path);
        if (!f.good()) path = "test/" + path;
    }

    vector<Vec3> vertices;
    vector<Face> faces;
    if (!loadOBJ(path, vertices, faces)) return 1;

    if (!vertices.empty()) {
        Box bbox = computeBoundingBox(vertices);
        Vec3 center = bbox.center();
        Vec3 half = bbox.halfSize();
        double maxDim = max({half.x, half.y, half.z});
        double scaleFactor = (maxDim > 0) ? (1.0 / maxDim) : 1.0;

        for (auto& v : vertices) {
            v.x = (v.x - center.x) * scaleFactor;
            v.y = (v.y - center.y) * scaleFactor;
            v.z = (v.z - center.z) * scaleFactor;
        }
    }

    const int width = 1000;
    const int height = 900;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow win(sf::VideoMode(width, height), "Pro Viewer", sf::Style::Titlebar | sf::Style::Close, settings);
    win.setFramerateLimit(60);

    double angX = 0.6, angY = 0.7;
    double zoom = 400.0;
    bool dragging = false;
    sf::Vector2i lastMouse;

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) win.close();
            if (e.type == sf::Event::MouseButtonPressed) {
                dragging = true;
                lastMouse = sf::Mouse::getPosition(win);
            }
            if (e.type == sf::Event::MouseButtonReleased) dragging = false;
            if (e.type == sf::Event::MouseWheelScrolled) zoom += e.mouseWheelScroll.delta * 20.0;
        }

        if (dragging) {
            sf::Vector2i cur = sf::Mouse::getPosition(win);
            angY += (cur.x - lastMouse.x) * 0.005;
            angX += (cur.y - lastMouse.y) * 0.005;
            lastMouse = cur;
        }

        win.clear(sf::Color::White);

        vector<FaceToDraw> drawList;
        for (const auto& face : faces) {
            int i0 = face.v1 - 1, i1 = face.v2 - 1, i2 = face.v3 - 1;
            if (i0 < 0 || i2 >= (int)vertices.size()) continue;

            Vec3 v0 = rotateY(rotateX(vertices[i0], angX), angY);
            Vec3 v1 = rotateY(rotateX(vertices[i1], angX), angY);
            Vec3 v2 = rotateY(rotateX(vertices[i2], angX), angY);

            Vec3 edge1 = v1 - v0;
            Vec3 edge2 = v2 - v0;
            Vec3 norm = edge1.cross(edge2);
            double len = sqrt(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z);
            if (len > 0) norm = {norm.x/len, norm.y/len, norm.z/len};
            
            if (norm.z < 0) continue;

            double light = 0.6 * norm.z + 0.3 * norm.y + 0.1;
            sf::Uint8 shade = static_cast<sf::Uint8>(100 + 155 * std::max(0.0, light));
            sf::Color color(shade, shade, shade);

            FaceToDraw ftd;
            ftd.v[0] = sf::Vertex(project(v0, zoom, width, height), color);
            ftd.v[1] = sf::Vertex(project(v1, zoom, width, height), color);
            ftd.v[2] = sf::Vertex(project(v2, zoom, width, height), color);
            ftd.zDepth = (float)(v0.z + v1.z + v2.z);
            drawList.push_back(ftd);
        }

        sort(drawList.begin(), drawList.end(), [](const FaceToDraw& a, const FaceToDraw& b) {
            return a.zDepth < b.zDepth;
        });

        for (const auto& f : drawList) {
            win.draw(f.v, 3, sf::Triangles);
        }

        win.display();
    }
    return 0;
}
