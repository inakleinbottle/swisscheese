
#include "catch.hpp"

#include "../src/swisscheese.hpp"


TEST_CASE( "Basic property tests", "[swisscheese]") {

    SwissCheese<double, double> sc {0.0, 1.0};

    CHECK(sc[0].centre() == 0.0);
    CHECK(sc[0].radius() == 1.0);

    REQUIRE(sc.length() == 0);

    SECTION("Index access") {
        sc.insert(0.5, 0.25);

        REQUIRE(sc.length() == 1);
        REQUIRE(sc[1].centre() == 0.5);
        REQUIRE(sc[1].radius() == 0.25);
    }

    SECTION("Multi disk") {
        sc.insert(0.0, 0.5);
        sc.insert(0.0, 0.25);
        sc.insert(0.0, 0.125);

        REQUIRE(sc.length() == 3);

        SECTION("Radius sum") {
            REQUIRE(sc.radius_sum() == 0.5 + 0.25 + 0.125);
        }

        SECTION("Discrepancy") {
            REQUIRE(sc.discrepancy() == 1.0 - 0.5 - 0.25 - 0.125);
        }
        
    }



}