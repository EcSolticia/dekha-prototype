#include "math.h"

double max(double a, double b, double c) {
    return std::max(a, std::max(b, c));
}
double min(double a, double b, double c) {
    return std::min(a, std::min(b, c));
}

Vector2 get_bounding_rect_topleft(Vector2 A, Vector2 B, Vector2 C) {
    Vector2 result;
    result.x = min(A.x, B.x, C.x);
    result.y = max(A.y, B.y, C.y);
    return result;
}
Vector2 get_bounding_rect_bottomright(Vector2 A, Vector2 B, Vector2 C) {
    Vector2 result;
    result.x = max(A.x, B.x, C.x);
    result.y = min(A.y, B.y, C.y);
    return result;
}