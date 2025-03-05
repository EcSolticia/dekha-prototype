#include <iostream>
#include <array>
#include "screen.h"
#include "node/polygon.h"
#include "node/camera.h"

int main() {
    Camera cam("Cam");
    cam.set_focal_length(0.5);
    Polygon Tri("Triangle");
    cam.add_to_channel(&Tri);
    
    Vec3f A = {0, 0, 1};
    Vec3f B = {0, 1, 1};
    Vec3f C = {1, 0, 1};
    Tri.add_triangle(A, B, C);

    Screen<10, 10> sc(0, 0);
    cam.set_screen(&sc);    

    try {
        Vec2f a = {0, 0};
        Vec2f b = {9, -9};
        Vec2f c = {9, 0};
        sc.draw_line(a, b);
        sc.draw_line(b, c);
        sc.draw_line(c, a);
    } catch (int e) {
        if (e == -1) {
            std::cout << "Caught error index out of range.\n";
            return 0;
        } else {
            std::cout << "Error. Quitting program" << std::endl;
            return 0;
        }
    }
    sc.output_display();

    std::cout << "Program executed without errors" << std::endl;

    return 0;
}
