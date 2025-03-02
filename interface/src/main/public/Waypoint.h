/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __WAYPOINT_H__
#define __WAYPOINT_H__

#include "Location.h"
#include "Direction.h"

struct Waypoint {
    Location location;
    Direction direction;
};

bool Waypoint_equals(const Waypoint& waypoint1, const Waypoint& waypoint2);

#endif