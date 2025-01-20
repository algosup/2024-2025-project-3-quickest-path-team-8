#include "../../includes/04-load/load.hpp"
#include "../../includes/02-extract/csv_reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Road> loadRoads(const std::string &filename) {

    // Create a container to store all the roads
    std::vector<Road> roads;

    // Open input file for reading
    std::ifstream file(filename);

    // Temporary string to hold each line in the file
    std::string line;

    // Read and discard the header line of the CSV file
    std::getline(file, line);

    // Read the remaining lines in the file
    while (std::getline(file, line)) {

        // Create a string stream to parse the line
        std::istringstream ss(line);

        // Temporary variables to hold parsed values
        std::string landmarkA, landmarkB, time;

        // Extract first value (landmarkA) from the string stream
        std::getline(ss, landmarkA, ',');

        // Extract second value (landmarkB) from the string stream
        std::getline(ss, landmarkB, ',');

        // Extract third value (time) from the string stream
        std::getline(ss, time, ',');

        // Convert parsed values to integers and add a Road object to vector
        roads.push_back({static_cast<int>(std::stoi(landmarkA)), static_cast<int>(std::stoi(landmarkB)), std::stod(time)});
    }

    // Return the vector containing all roads
    return roads;
}

/// Function to load road data from a binary file
std::vector<Road> loadRoadsFromBinary(const std::string &filename) {
    std::vector<Road> roads;
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Unable to open binary file " << filename << std::endl;
        return roads;
    }

    Road road;

    while (file.read(reinterpret_cast<char*>(&road), sizeof(Road))) {
        roads.push_back(road);
    }

    if (roads.empty()) {
        std::cerr << "Error: No data read from binary file " << filename << std::endl;
    }

    return roads;
}

/// Function to build a graph from the list of roads
std::unordered_map<int, std::vector<std::pair<int, double>>> buildGraph(const std::vector<Road> &roads) {

    // Create an adjacency list representation of the graph
    std::unordered_map<int, std::vector<std::pair<int, double>>> graph;

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