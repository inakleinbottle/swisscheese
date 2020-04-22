#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../src/swisscheese.hpp"


TEST_CASE( "Basic property tests", "[swisscheese]") {

    SwissCheese<double, double> sc {0.0, 1.0};

    REQUIRE(sc.length() == 0);

    sc.insert(0.5, 0.25);
    sc.insert(-0.5, 0.25);
    
    REQUIRE(sc.length() == 2);

    SECTION("Index access") {
        REQUIRE(sc[0].centre() == 0.5);
        REQUIRE(sc[0].radius() == 0.25);
    }


}