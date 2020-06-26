#include "catch.hpp"

#include <cmath>
#include "swisscheese.hpp"
#include <iostream>

using namespace swisscheese;
using namespace swisscheese::classicalise;


class Point2D {
    public:
    double x, y;

    Point2D(double x, double y) : x{x}, y{y} {}

    bool operator==(const Point2D &other) const {
        return (this->x == other.x) && (this->y == other.y);
    }

};

typedef Disk<Point2D, double> Disk2D;

std::ostream &operator<<(std::ostream &os, Point2D &point) {
    return os << "(" << point.x << ", " << point.y << ")";
}


void convex_comb(Point2D &p1, const Point2D &p2, double coeff) {
    double x, y, coeffm1;
    coeffm1 = 1.0 - coeff;

    x = coeff*p1.x + coeffm1*p2.x;
    y = coeff*p1.y + coeffm1*p2.y;

    p1.x = x;
    p1.y = y;
}

double euc_dist(const Point2D &p1, const Point2D &p2) {
    double diffx, diffy;
    diffx = p1.x - p2.x;
    diffy = p1.y - p2.y;

    return sqrt(pow(diffx, 2.0) + pow(diffy, 2.0));
}


TEST_CASE("Combining disks", "[combine]") {

    Point2D p1 {0.0, 0.0};
    Point2D p2 {1.0, 0.0};
    double r1 = 0.75, r2=0.75;

    Disk2D d1 {p1, r1};
    Disk2D d2 {p2, r2};
    // These disks overlap over an interval of width 0.5
    // at x = 0.5. The smallest containing disk has centre
    // {0.5, 0.0} and radius 1.25
    Point2D p3 {0.5, 0.0};
    double r3 = 1.25;

    Disk2D d3 = {p3, r3};

    REQUIRE(d3.contains(d1, euc_dist));
    REQUIRE(d3.contains(d2, euc_dist));

    SECTION("Combine 2 disks") {
        Disk2D new_disk = combine_disks(d1, d2, euc_dist, convex_comb);

        std::cerr << new_disk << " , " << d3 << std::endl;
        REQUIRE(new_disk == d3);
    }
    






}