/**
 * @file main.cpp
 * @brief Entry point for the road network path-finding application
 * 
 * Initializes the graph data structure, loads network data, and starts the web server.
 * Provides REST API endpoints for path-finding operations.
 */

#include "includes/binary.hpp"
#include "includes/graph.hpp"
#include "includes/dijkstra.hpp"
#include "includes/rest_api.hpp"
#include <iostream>
#include <cstdlib>


int main() {
    // CSV to binary conversion commented out - only needed for initial data prep
    // convertCSVtoBinary("../data/USA-road_sorted.csv", "../data/graph.bin");

    // Initialize path-finding engine with optimized graph structure
    PathFinder graph;

    // Load pre-processed binary graph data
    // Binary format provides faster loading and reduced memory footprint
    graph.loadGraphFromBinary("../data/graph.bin");

    // Launch web UI in default browser
    // Note: Mac-specific command, would need modification for other platforms
    system("open index.html");

    // Start REST API server
    // Handles path-finding requests from web UI
    // Blocks until process termination
    startServer(graph);

    return 0;
}