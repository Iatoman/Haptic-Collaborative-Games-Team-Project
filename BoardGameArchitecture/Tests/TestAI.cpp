#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Map.h"

// First Test Case
TEST_CASE("class map1 tests"){
	// Definition of the first grid
    int Grid1[5][5] = {
            { 1, 1, 0, 0, 0},
            { 0, 0, 1, 0, 0},
            { 0, 1, 0, 0, 0},
            { 0, 0, 1, 1, 0},
            { 0, 0, 0, 0, 1}
    };
	// The size of the first map is 5 X 5
    Map map1(5, 5);
	// Justify whether the map is created correctly and validly
    REQUIRE(map1.isValid(1, 1) == true);
    REQUIRE(map1.isValid(4, 4) == true);
    REQUIRE(map1.isValid(5, 5) == false);
	REQUIRE(map1.isValid(8, 8) == false);
	// Set the start point of the first map
    map1.setSource(0, 0);
	// Set the destination point of the first map
    map1.setDestination(4, 4);
	// Justify whether destination point is reached
    REQUIRE(map1.isDestination(4, 4) == true);
	REQUIRE(map1.isDestination(2, 3) == false);
	// Justify whether the point is blocked (now the grid has not been set)
	REQUIRE(map1.isUnBlocked(0, 1) == false);
	REQUIRE(map1.isUnBlocked(1, 2) == false);
    REQUIRE(map1.isUnBlocked(2, 2) == false);
    REQUIRE(map1.isUnBlocked(4, 0) == false);
    int* grid_p1[5];
    for(int i = 0; i < 5; i++){
        grid_p1[i] = Grid1[i];
    }
	// Set the grid
    map1.setGrid(grid_p1);
	// Justify whether the point is blocked (now the grid has been set)
    REQUIRE(map1.isUnBlocked(0, 1) == true);
	REQUIRE(map1.isUnBlocked(1, 2) == true);
    REQUIRE(map1.isUnBlocked(2, 2) == false);
    REQUIRE(map1.isUnBlocked(4, 0) == false);
    map1.aStarSearch();
}

// Second Test Case
TEST_CASE("class map2 tests"){
	// Definition of the second grid
    int Grid2[15][15] = {
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };
	// The size of the second map is 15 X 15
    Map map2(15, 15);
	// Justify whether the map is created correctly and validly
    REQUIRE(map2.isValid(1, 1) == true);
    REQUIRE(map2.isValid(4, 4) == true);
    REQUIRE(map2.isValid(15, 15) == false);
	REQUIRE(map2.isValid(16, 16) == false);
	// Set the start point of the second map
    map2.setSource(14, 0);
	// Set the destination point of the second map
    map2.setDestination(13, 14);
	// Justify whether destination point is reached
    REQUIRE(map2.isDestination(13, 14) == true);
	REQUIRE(map2.isDestination(9, 7) == false);
	// Justify whether the point is blocked (now the grid has not been set)
    REQUIRE(map2.isUnBlocked(0, 0) == false);
    REQUIRE(map2.isUnBlocked(0, 2) == false);
    REQUIRE(map2.isUnBlocked(1, 1) == false);
    REQUIRE(map2.isUnBlocked(2, 2) == false);
    REQUIRE(map2.isUnBlocked(13, 0) == false);
    REQUIRE(map2.isUnBlocked(14, 14) == false);
    REQUIRE(map2.isUnBlocked(13, 14) == false);
    int* grid_p2[15];
    for(int i = 0; i < 15; i++){
        grid_p2[i] = Grid2[i];
    }
	// Set the grid
    map2.setGrid(grid_p2);
	// Justify whether the point is blocked (now the grid has been set)
    REQUIRE(map2.isUnBlocked(0, 0) == true);
    REQUIRE(map2.isUnBlocked(0, 2) == true);
    REQUIRE(map2.isUnBlocked(1, 1) == false);
    REQUIRE(map2.isUnBlocked(2, 2) == false);
    REQUIRE(map2.isUnBlocked(13, 0) == false);
    REQUIRE(map2.isUnBlocked(14, 14) == false);
    REQUIRE(map2.isUnBlocked(13, 14) == true);
    map2.aStarSearch();
}