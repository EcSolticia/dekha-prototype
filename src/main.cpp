#include <iostream>
#include <array>
#include "screen.h"
#include "node/polygon.h"
#include "node/camera.h"

int main() {
    
    Screen<10, 10> main_screen(5, 5);
    Camera cam;
    main_screen.set_cam(&cam);
    Vec2f d = {2, 2};
    cam.set_dimensions(d);

    try {
        std::cout << "\n";
        std::cout << "Vertices with different z values will appear identical:\n";
        for (size_t i = 0; i < 10; ++i) {
            Vec3f X = {0, 0, (double)(i + 1)};
            Vec2f Y = main_screen.map_vertex_to_screen(X);
        }
        std::cout << "\n";
        std::cout << "Vertices with identical angles w.r.t. the camera origin appear on the same pixel\n";
        for (size_t i = 0; i < 10; ++i) {
            Vec3f X = {(double)(i + 1), 0, (double)(i + 1)};
            Vec2f Y = main_screen.map_vertex_to_screen(X);
        }
        std::cout << "\n";
        std::cout << "Upward scaling is twice" << std::endl;
        for (size_t i = 0; i < 10; ++i) {
            Vec3f X = {0, (double)(i + 1), (double)(i + 1)};
            Vec2f Y = main_screen.map_vertex_to_screen(X);
        }


    } catch (int e) {
        if (e == -1) {
            std::cout << "Caught error index out of range.\n";
            return 0;
        } else {
            std::cout << "Error. Quitting program" << std::endl;
            return 0;
        }
    }

    std::cout << "Program executed without errors" << std::endl;

    return 0;
}
