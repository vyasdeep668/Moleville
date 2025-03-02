/*
 * Copyright Kardium Inc. 2024.
 */

#include "Waypoint.h"

bool Waypoint_equals(const Waypoint& waypoint1, const Waypoint& waypoint2) {
    return waypoint1.location == waypoint2.location &&
            waypoint1.direction == waypoint2.direction;
}