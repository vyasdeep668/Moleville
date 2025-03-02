/*
 * Copyright Kardium Inc. 2024.
 */

#include <cassert>
#include "Location.h"

static const char* names[] = {
    "Entrance",
    "Slide",
    "School",
    "Playground",
    "Community Centre",
    "Market",
    "Public Works",
    "Pool",
    "Museum",
    "Theatre"
};

const char* Location_getName(Location location) {
    return names[location];
}