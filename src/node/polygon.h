#pragma once
#include "node.h"
#include "../common/types.h"
#include <vector>

class Polygon : public Node {
    std::vector<Vec3f> data;

public:
    void add_triangle(const Vec3f A, const Vec3f B, const Vec3f C);

    Polygon();
    ~Polygon() override;
};