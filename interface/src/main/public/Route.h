/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "Waypoint.h"

/**
 * A list of waypoints to get from a starting location to a finishing location.
 */
struct Route {
    int numWaypoints;
    int travelTimeMinutes;
    Waypoint waypoints[NUM_LOCATIONS];
};

/**
 * Initializes a route, performing defensive copying.
 *
 * @param route                 The route to initialize.
 * @param waypoints             An array of waypoints from start to finish.
 * @param numWaypoints          The number of waypoints in the array.  If
 *                              zero then the route is a null-route.
 * @param travelTimeMinutes     The expected travel time in minutes.
 */
void Route_init(Route& route, const Waypoint waypoints[], int numWaypoints,
                int travelTimeMinutes);

/**
 * Determines whether a route is a null-route.
 *
 * @param route     A route.
 * @return true if the route is a null-route (i.e. it has no waypoints).
 */
bool Route_isNull(const Route& route);

/**
 * Obtains the route's starting point.
 *
 * @param route     A route.
 * @return the location at the start of the route.  The return value is
 * undefined if the route is a null-route.
 */
Location Route_getStart(const Route& route);

/**
 * Obtains the route's finishing point.
 *
 * @param route     A route.
 * @return the location at the finish of the route.  The return value is
 * undefined if the route is a null-route.
 */
Location Route_getFinish(const Route& route);

/**
 * Prints a route to standard output.
 *
 * @param route     A route.  If it is a null-route then "No route found"
 * is printed.
 */
void Route_print(const Route& route);

/**
 * Route equality check.
 *
 * @param route1    A route.
 * @param route2    Another route.
 * @return true if the routes have the same waypoints and travel time.
 */
bool Route_equals(const Route& route1, const Route& route2);

#endif