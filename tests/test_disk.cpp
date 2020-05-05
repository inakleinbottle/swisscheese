

#include "catch.hpp"

#include <math.h>

#include "../src/swisscheese.hpp"

double dist(const double a, const double b) {
    return std::fabs(b - a);
}
typedef Disk<double, double> disk_t;


TEST_CASE( "Basic disk tests", "[disk]") {

    disk_t disk {0.0, 1.0};
    
    SECTION ("Attribute access") {
        CHECK(disk.centre() == 0.0);
        REQUIRE(disk.radius() == 1.0);
    }

}

TEST_CASE( "Disk interactions", "[disk]" ) {
    disk_t d1 {0.0, 1.0};
    disk_t d2 {1.0, 0.5};

    SECTION( "Overlap computation" ) {
        REQUIRE(d1.overlap(d2, dist) == 1.0 - 1.0 - 0.5);
    }


    SECTION( "Comparisons" ) {
        disk_t d3 {0.0, 0.6};

        CHECK(d3.inside(d1, dist));
        CHECK(d3.inside_proper(d1, dist));
        CHECK(d1.contains_proper(d1, dist));

    }

}