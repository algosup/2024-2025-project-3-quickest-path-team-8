/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

g++ -std=c++17 -O1 -march=native main.cpp graph.cpp dijkstra.cpp binary.cpp rest_api.cpp -o api && ./api 

*/

#include "includes/binary.hpp"
#include "includes/graph.hpp"
#include "includes/dijkstra.hpp"
#include "includes/rest_api.hpp"
#include <iostream>
#include <cstdlib>


// fromm binary 

int main() {
    // // Convert CSV to binary
    // convertCSVtoBinary("../data/USA-road_sorted.csv", "../data/graph.bin");

    PathFinder graph; // create an instance of the graph 

    // Load the graph from the binary file
    graph.loadGraphFromBinary("../data/graph.bin");

    // Open the UI in the default browser
    system("open index.html");

    // Start the server
    startServer(graph);

    return 0;
}