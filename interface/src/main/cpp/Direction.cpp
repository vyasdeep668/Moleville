/*
 * Copyright Kardium Inc. 2024.
 */

#include <cassert>
#include "Direction.h"

static const char* names[] = {
    "North",
    "South",
    "West",
    "East",
    "FINISH"
};

const char* Direction_getName(Direction direction) {
    return names[direction];
}
