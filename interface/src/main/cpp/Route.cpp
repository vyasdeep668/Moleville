/*
 * Copyright Kardium Inc. 2024.
 */

#include <cassert>
#include <stdio.h>
#include <string.h>
#include "Route.h"


void Route_init(Route& route, const Waypoint waypoints[], int numWaypoints, int travelTimeMinutes) {
    assert(numWaypoints == 0 || waypoints != 0);
    assert(numWaypoints >= 0);
    assert(numWaypoints < NUM_LOCATIONS);

    memset(&route, 0, sizeof(Route));
    route.numWaypoints = numWaypoints;
    route.travelTimeMinutes = travelTimeMinutes;

    for (int i = 0; i < numWaypoints; i++) {
        route.waypoints[i] = waypoints[i];
    }
}


bool Route_isNull(const Route& route) {
    return route.numWaypoints == 0;
}


Location Route_getStart(const Route& route) {
    return Route_isNull(route) ? Entrance : route.waypoints[0].location;
}


Location Route_getFinish(const Route& route) {
    return Route_isNull(route) ? Entrance : route.waypoints[route.numWaypoints - 1].location;
}


void Route_print(const Route& route) {
    if (Route_isNull(route)) {
        printf("No route found\n");
    } else {
        Location start = Route_getStart(route);
        Location finish = Route_getFinish(route);
        printf("Route from %s to %s (%d minutes):\n",
                Location_getName(start), Location_getName(finish), route.travelTimeMinutes);

        for (int i = 0; i < route.numWaypoints; i++) {
            printf("\t%s : %s\n",
                    Location_getName(route.waypoints[i].location),
                    Direction_getName(route.waypoints[i].direction));
        }
    }
}


bool Route_equals(const Route& route1, const Route& route2) {
    if (Route_isNull(route1)) {
        return Route_isNull(route2);
    }
    if (route1.numWaypoints != route2.numWaypoints ||
            route1.travelTimeMinutes != route2.travelTimeMinutes) {
        return false;
    }
    for (int i = 0; i < route1.numWaypoints; i++) {
        if (!Waypoint_equals(route1.waypoints[i], route2.waypoints[i])) {
            return false;
        }
    }
    return true;
}