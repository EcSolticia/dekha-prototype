#pragma once 
#include <cmath>
#include "types.h"

double max(double a, double b, double c);
double min(double a, double b, double c);

Vector2 get_bounding_rect_topleft(Vector2 A, Vector2 B, Vector2 C);
Vector2 get_bounding_rect_bottomright(Vector2 A, Vector2 B, Vector2 C);