#include <iostream>
#include <array>
#include "screen.h"
#include "node/polygon.h"
#include "node/camera.h"

#include "common/meshgen.h"

int main() {
    
    Screen<50, 50> main_screen(25, 25);
    Camera cam;
    main_screen.set_cam(&cam);
    Vec2f d = {50, 50};
    cam.set_dimensions(d);

    try {
        
        Polygon tri("Triangle");
        main_screen.draw_triangle_face(tri.get_data());

    } catch (const std::out_of_range& err) {
        std::cerr << "Error: out_of_range - " << err.what() << std::endl;
        return 1;
    } catch (const std::domain_error& err) {
        std::cerr << "Error: domain_error - " << err.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& err) {
        std::cerr << "Error: runtime_error - " << err.what() << std::endl;
        return 1;
    } catch (const std::exception& err) {
        std::cerr << "Unexpected error - " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    main_screen.output_display();

    std::cout << "Program executed successfully" << std::endl;

    return 0;
}
