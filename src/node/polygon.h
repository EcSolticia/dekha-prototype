#pragma once
#include "node.h"
#include <vector>

class Polygon : public Node {
    std::vector<Vec3f> data;

public:
    void add_triangle(const Vec3f A, const Vec3f B, const Vec3f C);

    std::vector<Vec3f> get_data();

    Polygon(const std::string name="Non-name");
    ~Polygon() override;
};