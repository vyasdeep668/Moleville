/*
 * Copyright Kardium Inc. 2024.
 */

 #include <stdio.h>
 #include "MoleGuide.h"
 #include "munit.h"
 
static void assertRoutesEqual(const char* message, const Route& expectedRoute, const Route& route) {
    bool success = mu_assert(message, Route_equals(expectedRoute, route));

    if (!success) {
        printf("Expected route:\n");
        Route_print(expectedRoute);

        printf("Actual route:\n");
        Route_print(route);
    }
}

// Test Case 0: Test the route from Entrance to Slide a to b -> 2minutes
static void test_a_to_b() {
    mu_startTest("a_to_b");
    Route expectedRoute = {2, 2, {{Entrance, North}, {Slide, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Slide));
    mu_finishTest();
}

// Test Case 1: Test the route from Entrance to Theatre a to j -> 6minutes
static void test_a_to_j() {
    mu_startTest("a_to_j");
    Route expectedRoute = {5, 6, {{Entrance, East}, {Community_Centre, West}, {Market, East}, {Public_Works, South}, {Theatre, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Theatre));
    mu_finishTest();
}

// Test Case 2: Test the route from Entrance to Market a to f -> 4minutes
static void test_a_to_f() {
    mu_startTest("a_to_f");
    Route expectedRoute = {3, 4, {{Entrance, East}, {Community_Centre, West}, {Market, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Market));
    mu_finishTest();
}

// Test Case 3: Test the route from School to Museum c to i -> 6minutes
static void test_c_to_i() {
    mu_startTest("c_to_i");
    Route expectedRoute = {4, 6, {{School, South}, {Slide, South}, {Pool, South}, {Museum, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(School, Museum));
    mu_finishTest();
}

// Test Case 4: Test the route from Entrance to Entrance a to a -> 0minutes
static void test_a_to_a() {
    mu_startTest("a_to_a");
    Route expectedRoute = {1, 0, {{Entrance, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Entrance));
    mu_finishTest();
}

// Test Case 5: Test the route from Entrance to Theatre a to b -> 14minutes (Tunnels a to b under maintenance)
static void test_a_to_b_with_tunnel_a_to_b_under_maintenance() {
    mu_startTest("a_to_b_with_tunnel_a_to_b_under_maintenance");
    reportCaveIn(Entrance, North);
    Route expectedRoute = {7, 14, {{Entrance, East}, {Community_Centre, West}, {Market, East}, {Public_Works, South}, {Theatre, East}, {School, South}, {Slide, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Slide));
    mu_finishTest();
}

// Test Case 6: Test the route from Entrance to Theatre a to b -> 14minutes (All tunnels from a closed)
static void test_a_to_b_with_all_tunnel_from_a_under_maintenance() {
    mu_startTest("a_to_b_with_all_tunnel_from_a_under_maintenance");
    reportCaveIn(Entrance, North);
    reportCaveIn(Entrance, East);
    Route expectedRoute = {0, 0, {}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Slide));
    reportCaveInCleared(Entrance, North);
    reportCaveInCleared(Entrance, East);
    mu_finishTest();
}

// Test Case 7: Test the route from Entrance to Slide after reopening the tunnel
static void test_a_to_b_after_reopening() {
    mu_startTest("a_to_b_after_reopening");
    reportCaveIn(Entrance, North);
    reportCaveInCleared(Entrance, North);
    Route expectedRoute = {2, 2, {{Entrance, North}, {Slide, FINISH}}};
    assertRoutesEqual(CODELOC, expectedRoute, findRoute(Entrance, Slide));
    mu_finishTest();
}



int main() {
    mu_init("MolevilleGuide", initGuide, 0);
    test_a_to_b();
    test_a_to_j();
    test_a_to_f();
    test_c_to_i();
    test_a_to_a();
    test_a_to_b_with_tunnel_a_to_b_under_maintenance();
    test_a_to_b_with_all_tunnel_from_a_under_maintenance();
    test_a_to_b_after_reopening();
    return mu_summary();
}