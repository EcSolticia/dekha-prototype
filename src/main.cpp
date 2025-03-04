#include <iostream>
#include <array>
#include "screen.h"
#include "node/polygon.h"
#include "node/camera.h"

int main() {
    Screen<10, 10> sc(0, 0);
    Vec2f A = {0, 0};
    Vec2f B = {5, 0};
    Vec2f C = {5, 0};

    try {
        sc.draw_line(A, B);
        sc.draw_line(B, C);
    } catch (int e) {
        if (e == -1) {
            std::cout << "Caught error index out of range, gracefully quitting program" << std::endl;
            return 0;
        }
    }
    sc.output_display();

    std::cout << "Program executed without errors" << std::endl;

    return 0;
}
