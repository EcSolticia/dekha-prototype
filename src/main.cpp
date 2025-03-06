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

    } catch (const std::out_of_range& err) {
        std::cerr << "Halting program due to out_of_range error" << std::endl;
        return 1;
    } catch (const std::domain_error& err) {
        std::cerr << "Halting program due to domain_error error" << std::endl;
        return 1;
    } catch (const std::runtime_error& err) {
        std::cerr << "Halting program due to runtime_error error" << std::endl;
        return 1;
    } catch (const std::exception& err) {
        std::cerr << "Unexpected error\n";
        std::cerr << "Program will not yet halt for debugging purposes, please take note of the following output" << std::endl;
    }

    main_screen.output_display();

    std::cout << "Program executed successfully" << std::endl;

    return 0;
}
