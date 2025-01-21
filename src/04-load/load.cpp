#include "../../includes/04-load/load.hpp"
#include "../../includes/02-extract/csv_reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Road> loadRoads(const string &filename) {

    // Create a container to store all the roads
    vector<Road> roads;

    // Open input file for reading
    ifstream file(filename);

    // Temporary string to hold each line in the file
    string line;

    // Read and discard the header line of the CSV file
    getline(file, line);

    // Read the remaining lines in the file
    while (getline(file, line)) {

        // Create a string stream to parse the line
        istringstream ss(line);

        // Temporary variables to hold parsed values
        string landmarkA, landmarkB, time;

        // Extract first value (landmarkA) from the string stream
        getline(ss, landmarkA, ',');

        // Extract second value (landmarkB) from the string stream
        getline(ss, landmarkB, ',');

        // Extract third value (time) from the string stream
        getline(ss, time, ',');

        // Convert parsed values to integers and add a Road object to vector
        roads.push_back({static_cast<int>(stoi(landmarkA)), static_cast<int>(stoi(landmarkB)), stod(time)});
    }

    // Return the vector containing all roads
    return roads;
}

/// Function to load road data from a binary file
vector<Road> loadRoadsFromBinary(const string &filename) {
    vector<Road> roads;
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "Error: Unable to open binary file " << filename << endl;
        return roads;
    }

    Road road;

    while (file.read(reinterpret_cast<char*>(&road), sizeof(Road))) {
        roads.push_back(road);
    }

    if (roads.empty()) {
        cerr << "Error: No data read from binary file " << filename << endl;
    }

    return roads;
}

/// Function to build a graph from the list of roads
unordered_map<int, vector<pair<int, double>>> buildGraph(const vector<Road> &roads) {

    // Create an adjacency list representation of the graph
    unordered_map<int, vector<pair<int, double>>> graph;

    // Iterates through all roads to populate the graph
    for (const auto &road : roads) {

        // Adds an edge from landmarkA to landmarkB with travel time
        graph[road.landmarkA].emplace_back(road.landmarkB, road.time);

        // Adds an edge from landmarkB to landmarkA with the same travel time
        graph[road.landmarkB].emplace_back(road.landmarkA, road.time);
    }

    // Returns the graph as an adjacency list
    return graph;
}


unordered_map<int, vector<pair<int, double>>> getAdjacencyList(const vector<Road> &roads) {
    unordered_map<int, vector<pair<int, double>>> adjacencyList;
    for (const auto &road : roads) {
        adjacencyList[road.landmarkA].push_back({road.landmarkB, road.time});
    }
    return adjacencyList;
}