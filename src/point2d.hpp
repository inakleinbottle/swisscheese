struct Point2D {
    double x, y;
};

/// Produce a linear combination of two points
Point2D linear_combination(const Point2D&, const Point2D&, double, double);


double l2_dist(const Point2D&, const Point2D&);