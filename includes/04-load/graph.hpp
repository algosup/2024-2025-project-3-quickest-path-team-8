#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Define a structure for edges in the graph
struct Edge {
    int destination;   // Destination node
    int travel_time;   // Edge weight (travel time)
};

// Ensure the structure matches the binary file format
#pragma pack(push, 1)
struct Road {
    int landmarkA; // Starting node
    int landmarkB; // Ending node
    int time;      // Travel time
};
#pragma pack(pop)

// Graph class to manage landmarks and connections
class Graph {
public:
    // Add a bidirectional edge between two landmarks
    void addEdge(int landmarkA, int landmarkB, int time) {
        adjList[landmarkA].push_back({landmarkB, time});  // Add edge A -> B
        adjList[landmarkB].push_back({landmarkA, time});  // Add edge B -> A (bidirectional)
    }

    // Load the graph from a binary file
    void loadGraphFromBinary(const string& filename) {
        ifstream file(filename, ios::binary);

        if (!file.is_open()) {
            cerr << "Error: Could not open binary file: " << filename << endl;
            return;
        }

        // Determine the size of the file
        file.seekg(0, ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, ios::beg);

        // Ensure the file size is a multiple of the Road structure size
        if (fileSize % sizeof(Road) != 0) {
            cerr << "Error: File size is not aligned with Road structure size." << endl;
            return;
        }

        // Calculate the number of Road records
        size_t numRecords = fileSize / sizeof(Road);

        // Read the binary data into a buffer
        vector<Road> roads(numRecords);
        file.read(reinterpret_cast<char*>(roads.data()), fileSize);

        if (!file) {
            cerr << "Error: Failed to read binary file: " << filename << endl;
            return;
        }

        // Add edges to the adjacency list
        for (const auto& road : roads) {
            addEdge(road.landmarkA, road.landmarkB, road.time);
        }

        cout << "Successfully loaded graph with " << roads.size() << " edges from binary file: " << filename << endl;
    }

    // Display the adjacency list for debugging or verification purposes
    void displayGraph() const {
        for (const auto& pair : adjList) {
            cout << "Landmark " << pair.first << " -> ";
            for (const auto& edge : pair.second) {
                cout << "(Dest: " << edge.destination 
                     << ", Time: " << edge.travel_time << ") ";
            }
            cout << "\n";
        }
    }

    // Get the adjacency list
    const unordered_map<int, vector<Edge>>& getAdjList() const {
        return adjList;
    }

private:
    unordered_map<int, vector<Edge>> adjList; // Adjacency list representation of the graph
};

#endif // GRAPH_HPP