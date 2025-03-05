#include <iostream>
#include <array>
#include "screen.h"
#include "node/polygon.h"
#include "node/camera.h"

int main() {
    
    Screen<50, 50> main_screen(25, 25);
    Camera cam;
    main_screen.set_cam(&cam);
    Vec2f d = {50, 50};
    cam.set_dimensions(d);

    try {
        
        // initialize object to draw
        Polygon tri("Triangle");
        main_screen.draw_polygon(&tri);

    } catch (int e) {
        if (e == -1) {
            std::cout << "Caught error index out of range.\n";
            return 0;
        } else {
            std::cout << "Error. Quitting program" << std::endl;
            return 0;
        }
    }

    main_screen.output_display();

    std::cout << "Program executed without errors" << std::endl;

    return 0;
}
