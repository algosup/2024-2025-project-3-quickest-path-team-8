
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <limits>
#include <unordered_set>

using namespace std;

// Edge structure optimized for fast traversal
struct Edge {
    int destination;   // Destination node
    int travel_time;   // Edge weight
};

// Road structure for binary file loading (aligned with binary data format)
#pragma pack(push, 1)
struct Road {
    int32_t landmarkA; // Starting node
    int32_t landmarkB; // Ending node
    int32_t time;      // Travel time
};
#pragma pack(pop)

// Compressed adjacency list representation of a graph
class Graph {
public:
    // Constructor
    Graph(size_t numNodes = 0, size_t numEdges = 0) {
        if (numNodes > 0) {
            adjacencyList.resize(numNodes); // Preallocate space for nodes
        }
    }

    // Add a bidirectional edge between two landmarks
    void addEdge(int landmarkA, int landmarkB, int time) {
        adjacencyList[landmarkA].emplace_back(Edge{landmarkB, time}); // A -> B
        adjacencyList[landmarkB].emplace_back(Edge{landmarkA, time}); // B -> A
    }

    // Load the graph from a binary file
    void loadGraphFromBinary(const string& filename) {
    // Open the binary file
    ifstream file(filename, ios::binary);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open binary file: " << filename << endl;
        return;
    }

    // Get the size of the file (in bytes)
    file.seekg(0, ios::end); // Move to the end of the file
    size_t fileSize = file.tellg(); // Get the current position (end of the file)
    file.seekg(0, ios::beg); // Move back to the beginning of the file

    // Ensure the file size is a multiple of the size of a Road structure
    if (fileSize % sizeof(Road) != 0) {
        cerr << "Error: File size is not aligned with the size of Road structures." << endl;
        return;
    }

    // Calculate the number of edges (each Road structure represents an edge)
    size_t numEdges = fileSize / sizeof(Road);

    // Temporary storage for unique node IDs to calculate the number of nodes
    unordered_set<int> uniqueNodes;

    // Create a vector to hold all edges (Road structures)
    vector<Road> roads(numEdges);

    // Read the entire file into the vector
    file.read(reinterpret_cast<char*>(roads.data()), fileSize);

    // Check if the file was read successfully
    if (!file) {
        cerr << "Error: Failed to read the binary file: " << filename << endl;
        return;
    }

    // Track the maximum node ID for adjacency list resizing
    int maxNodeID = 0;

    // Process each road in the vector
    for (const auto& road : roads) {
        // Add both nodes to the set of unique nodes
        uniqueNodes.insert(road.landmarkA);
        uniqueNodes.insert(road.landmarkB);

        // Update the maximum node ID
        maxNodeID = max({maxNodeID, road.landmarkA, road.landmarkB});
    }

    // Resize the adjacency list to accommodate the highest node ID
    adjacencyList.resize(maxNodeID + 1);

    // Add edges to the adjacency list
    for (const auto& road : roads) {
        addEdge(road.landmarkA, road.landmarkB, road.time);
    }

    // Print a success message with the total number of nodes and edges
    size_t numNodes = uniqueNodes.size();
    cout << "Successfully loaded graph with " << numNodes << " nodes and " << numEdges
         << " edges from binary file: " << filename << endl;
    }

    // Display the adjacency list for debugging
    void displayGraph() const {
        for (size_t i = 0; i < adjacencyList.size(); ++i) {
            if (!adjacencyList[i].empty()) {
                cout << "Node " << i << " -> ";
                for (const auto& edge : adjacencyList[i]) {
                    cout << "(Dest: " << edge.destination << ", Time: " << edge.travel_time << ") ";
                }
                cout << "\n";
            }
        }
    }

    // Get the adjacency list
    const vector<vector<Edge>>& getAdjacencyList() const {
        return adjacencyList;
    }

    // Get the number of nodes in the graph
    size_t getNumNodes() const {
        return adjacencyList.size();
    }

private:
    vector<vector<Edge>> adjacencyList; // Compressed adjacency list for fast neighbor access
};
