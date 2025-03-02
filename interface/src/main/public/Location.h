/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __LOCATION_H__
#define __LOCATION_H__

#define NUM_LOCATIONS   (10)

typedef enum {
    Entrance,
    Slide,
    School,
    Playground,
    Community_Centre,
    Market,
    Public_Works,
    Pool,
    Museum,
    Theatre
} Location;

const char* Location_getName(Location location);

#endif