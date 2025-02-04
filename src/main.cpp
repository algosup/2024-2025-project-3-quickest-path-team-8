/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    Main Program
    This program will...

*/

#include "includes/binary.hpp"
#include "includes/graph.hpp"
#include "includes/dijkstra.hpp"

// fromm binary 

int main() {
    // Convert CSV to binary
    convertCSVtoBinary("../data/USA-roads.csv", "../data/graph.bin");

    PathFinder graph; // create an instance of the graph 

    // Load the graph from the binary file
    auto start = std::chrono::high_resolution_clock::now();
    graph.loadGraphFromBinary("../data/graph.bin");
    auto end = std::chrono::high_resolution_clock::now();
    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time to load graph: " << loadTime << " ms\n";

    return 0;
}