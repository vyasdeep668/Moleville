/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __MOLEGUIDE_H__
#define __MOLEGUIDE_H__

#include "Location.h"
#include "Route.h"

/**
 * Initializes the guide.
 */
void initGuide();

/**
 * Finds the fastest route from the starting location to
 * the finishing location.
 *
 * @param start     The location to start from.
 * @param finish    The location to finish at.
 * @return the route found.  If multiple routes are possible
 * then no route shall be shorter than this one.  If the
 * destination is unreachable then the result shall be a
 * null-route.  The result will be overwritten on the next
 * call to findRoute().
 */
const Route& findRoute(Location start, Location finish);

/**
 * Reports the collapse of a tunnel.  Subsequent calls
 * to {@link #findRoute()} will avoid this tunnel.
 *
 * @param nearby    A location nearby the collapsed tunnel.
 * @param direction The direction of the collapsed tunnel from the
 *                  location.
 * @returns zero if successful, non-zero if there is no tunnel at the
 * specified location and direction, or the specified tunnel cannot be
 * entered from that direction.
 */
int reportCaveIn(Location nearby, Direction direction);

/**
 * Reports that a collapsed tunnel has been repaired.  Subsequent
 * calls to {@link #findRoute()} will no longer avoid this tunnel.
 *
 * @param nearby        A location nearby the repaired tunnel.
 * @param direction     The direction of the repaired tunnel from the
 *                      location.
 * @returns zero if successful, non-zero if there is no tunnel at the
 * specified location and direction, or the specified tunnel cannot be
 * entered from that direction.
 */
int reportCaveInCleared(Location nearby, Direction direction);

#endif