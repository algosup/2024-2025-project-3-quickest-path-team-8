// RUN WITH:
// g++ -std=c++17 -O1 -march=native "test.cpp" "../src/binary.cpp" "../src/graph.cpp" "../src/dijkstra.cpp" -o test && ./test && rm test

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "../src/includes/binary.hpp" // Include the Graph base class
#include "../src/includes/graph.hpp" // Include the Graph base class
#include "../src/includes/dijkstra.hpp" // Include the Graph base class


int main() {
    PathFinder graph; // create an instance of the graph 

    // Add code to verify the existence of the binary file
    // if it doesn't exist, then create it
    if (!std::ifstream("../data/graph.bin").good()) {
        convertCSVtoBinary("../data/USA-roads.csv", "../data/graph.bin");
    }

    // Load the graph from the binary file
    auto start = std::chrono::high_resolution_clock::now();
    graph.loadGraphFromBinary("../data/graph.bin");
    auto end = std::chrono::high_resolution_clock::now();
    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time to load graph: " << loadTime << " ms\n";

    // Define landmarks (source-destination pairs)
    std::vector<std::pair<int, int>> landmarkPairs = {
        {1, 18},  
        {500, 70000},
        {50, 700000},
        {3930, 976358},
        {9489093, 22377087} 
    };

    // Loop through the landmark pairs and test Dijkstra's algorithm
    for (size_t i = 0; i < landmarkPairs.size(); ++i) {
        int source = landmarkPairs[i].first;
        int destination = landmarkPairs[i].second;

        std::cout << "Test " << i + 1 << ": Source = " << source << ", Destination = " << destination << "\n";

        // Measure time for Bidirectional Dijkstra
        start = std::chrono::high_resolution_clock::now();
        auto result = graph.bidirectionalDijkstra(source, destination);
        end = std::chrono::high_resolution_clock::now();
        auto dijkstraTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time to execute Bidirectional Dijkstra: " << dijkstraTime << " ms\n";

        // Output the results
        int travelTime = result.first;
        std::vector<int> path = result.second;

        std::cout << "Shortest travel time: " << travelTime << "\n";
        // cout << "Path: ";
        // for (int landmark : path) {
        //     cout << landmark << " ";
        // }
        std::cout << "\n\n";
    }

    return 0;
}