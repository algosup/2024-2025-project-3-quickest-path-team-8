#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "../src/dijkstra.cpp" // Include the Graph base class

using namespace std;

int main() {
    PathFinder graph; // create an instance of the graph 

    // Load the graph from the binary file
    auto start = chrono::high_resolution_clock::now();
    graph.loadGraphFromBinary("../data/graph_data.bin");
    auto end = chrono::high_resolution_clock::now();
    auto loadTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Time to load graph: " << loadTime << " ms\n";

    // Define landmarks (source-destination pairs)
    vector<pair<int, int>> landmarkPairs = {
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

        cout << "Test " << i + 1 << ": Source = " << source << ", Destination = " << destination << "\n";

        // Measure time for Bidirectional Dijkstra
        start = chrono::high_resolution_clock::now();
        auto result = graph.bidirectionalDijkstra(source, destination);
        end = chrono::high_resolution_clock::now();
        auto dijkstraTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "Time to execute Bidirectional Dijkstra: " << dijkstraTime << " ms\n";

        // Output the results
        int travelTime = result.first;
        vector<int> path = result.second;

        cout << "Shortest travel time: " << travelTime << "\n";
        // cout << "Path: ";
        // for (int landmark : path) {
        //     cout << landmark << " ";
        // }
        cout << "\n\n";
    }

    return 0;
}