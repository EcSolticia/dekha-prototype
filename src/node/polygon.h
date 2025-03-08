#pragma once
#include "node.h"
#include <vector>

class Polygon : public Node {
    std::vector<Vector3> data;

public:

    void set_data(const std::vector<Vector3> data);
    std::vector<Vector3> get_data() const;

    Polygon(const std::string name="Non-name");
    ~Polygon() override;
};