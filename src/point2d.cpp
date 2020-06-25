#include <cmath>
#include "src/point2d.hpp"

Point2D
linear_combination(const Point2D &point_a, const Point2D &point_b,
                    double lambda, double mu) {
    return Point2D {
        x: lambda*point_a.x + mu*point_b.x,
        y: lambda*point_a.y + mu*point_b.y
    };
}


double
l2_dist(const Point2D &point_a, const Point2D &point_b) {
    long double x = point_a.x - point_b.x;
    long double y = point_a.y - point_b.y;
    return sqrt(pow(x, 2) + pow(y, 2));
}

