/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#define NUM_DIRECTIONS  ((int) FINISH)

typedef enum {
    North,
    South,
    West,
    East,
    FINISH
} Direction;

const char* Direction_getName(Direction direction);

#endif