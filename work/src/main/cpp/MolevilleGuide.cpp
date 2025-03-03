/*
* Copyright Kardium Inc. 2024.
*/

#include "MoleGuide.h"
#include <queue>
#include <unordered_map>
#include <limits.h>
 
using namespace std;
 
static Route route;
 
// Tunnel between two locations
struct Tunnel 
{
    Location destination;
    Direction direction;
    int time;
    bool isUnderMaintenance;
};
 
// MoleGuide Map {Current_Location, {Destination_Location, Direction, Time, isUnderMaintenance}}
unordered_map<Location, vector<Tunnel>> MoleGuideMap;

/**
* Initializes the MoleGuide Map with given map in pdf.
*
* @param None
* @return None
*/
void initGuide() 
{
    MoleGuideMap.clear();

    
    MoleGuideMap[Entrance]          = {{Slide, North, 2, false}, {Community_Centre, East, 3, false}};                       // a - Entrance
    MoleGuideMap[Slide]             = {{Entrance, East, 2, false}, {School, North, 2, false}, {Pool, South, 2, false}};     // b - Slide
    MoleGuideMap[School]            = {{Slide, South, 3, false}, {Playground, East, 1, false}};                             // c - School
    MoleGuideMap[Playground]        = {{Community_Centre, South, 2, false}};                                                // d - Playground
    MoleGuideMap[Community_Centre]  = {{Entrance, North, 3, false}, {Market, West, 1, false}};                              // e - Community Centre
    MoleGuideMap[Market]            = {{Public_Works, East, 1, false}};                                                     // f - Market
    MoleGuideMap[Public_Works]      = {{Community_Centre, North, 1, false},{Theatre, South, 1, false}};                     // g - Public Works
    MoleGuideMap[Pool]              = {{Market, East, 4, false}, {Museum, South, 1, false}};                                // h - Pool
    MoleGuideMap[Museum]            = {{Theatre, East, 2, false}};                                                          // i - Museum
    MoleGuideMap[Theatre]           = {{School, East, 5, false}, {Museum, South, 3, false}};                                // j - Theatre
}

/**
* Finds the fastest route from the starting location to
* the finishing location.
* Note: Uses Dijkstra's algorithm to find the shortest path
* using priority queue.
* @param start The location to start from.
* @param finish The location to finish at.
* @return the route found. If multiple routes are possible
* then no route shall be shorter than this one. If the
* destination is unreachable then the result shall be a
* null-route. The result will be overwritten on the next
* call to findRoute().
*/
const Route& findRoute(Location start, Location finish) 
{
    // Data structures for Dijkstra's algorithm
    unordered_map<Location, int> dist;
    unordered_map<Location, Waypoint> prev;         // To store the previous location and direction
    priority_queue<pair<int, Location>, vector<pair<int, Location>>, greater<pair<int, Location>>> pq;      // pq for Dijkstra's algorithm

    // Initialize distances
    for (int i = 0; i < NUM_LOCATIONS; i++) 
    {
        dist[(Location)i] = INT_MAX;
    }
    dist[start] = 0;
    pq.push({0, start});

    // Dijkstra's algorithm
    while (!pq.empty()) 
    {
        Location currLoc = pq.top().second;
        pq.pop();

        if (currLoc == finish) 
        {
            break;
        }

        // Visit all children location of current location
        for (auto tunnel : MoleGuideMap[currLoc]) 
        {
            if (tunnel.isUnderMaintenance) 
            {
                continue; // Skip Under Maintenance tunnels
            }

            Location childLoc = tunnel.destination;
            int weight = tunnel.time;

            if (dist[currLoc] + weight < dist[childLoc]) 
            {
                dist[childLoc] = dist[currLoc] + weight;
                prev[childLoc] = {currLoc, tunnel.direction};   // Store the direction from u to v
                pq.push({dist[childLoc], childLoc});            // Push the {distance, child location} to the pq
            }
        }
    }

    // No route found in the map
    if (dist[finish] == INT_MAX) 
    {
        // No route found, return a null route
        Route_init(route, nullptr, 0, 0);
        return route;
    }

    // Build the waypoints
    Waypoint waypoints[NUM_LOCATIONS];
    int numWaypoints = 0;

    waypoints[numWaypoints++] = {finish, FINISH};
    for(Location currLoc = finish; currLoc != start; currLoc = prev[currLoc].location)
    {
        waypoints[numWaypoints++] = prev[currLoc];
    }

    // Reverse the waypoints since we traversed from finish to start
    for (int i = 0; i < numWaypoints/2; i++) 
    {
        swap(waypoints[i], waypoints[numWaypoints - 1 - i]);
    }

    // Initialize the route
    Route_init(route, waypoints, numWaypoints, dist[finish]);
    return route;
}
 
/**
* Reports the collapse of a tunnel. Subsequent calls
* to {@link #findRoute()} will avoid this tunnel.
*
* @param nearby A location nearby the collapsed tunnel.
* @param direction The direction of the collapsed tunnel from the
* location.
* @returns zero if successful, non-zero if there is no tunnel at the
* specified location and direction, or the specified tunnel cannot be
* entered from that direction.
*/
int reportCaveIn(Location nearby, Direction direction) 
{
    // Search for the tunnel in the specified direction
    for (Tunnel& tunnel : MoleGuideMap[nearby]) 
    {
        if (tunnel.direction == direction) 
        {
            tunnel.isUnderMaintenance = true;
            return 0; // Success
        }
    }
    return -1; // Tunnel not found
}
 
/**
* Reports that a collapsed tunnel has been repaired. Subsequent
* calls to {@link #findRoute()} will no longer avoid this tunnel.
*
* @param nearby A location nearby the repaired tunnel.
* @param direction The direction of the repaired tunnel from the
* location.
* @returns zero if successful, non-zero if there is no tunnel at the
* specified location and direction, or the specified tunnel cannot be
* entered from that direction.
*/
int reportCaveInCleared(Location nearby, Direction direction) 
{
    // Search for the tunnel in the specified direction
    for (Tunnel& tunnel : MoleGuideMap[nearby]) 
    {
        if (tunnel.direction == direction) 
        {
            tunnel.isUnderMaintenance = false;
            return 0; // Success
        }
    }
    return -1; // Tunnel not found
}