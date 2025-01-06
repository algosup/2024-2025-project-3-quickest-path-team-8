
// Import httlib from the same directory
#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Structure to hold road data
struct Road {
    int landmarkA;
    int landmarkB;
    int time;
};


// Function to load roads from the CSV file
std::vector<Road> loadRoads(const std::string &filename) {
    std::vector<Road> roads;
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string landmarkA, landmarkB, time;

        std::getline(ss, landmarkA, ',');
        std::getline(ss, landmarkB, ',');
        std::getline(ss, time, ',');

        roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});
    }

    return roads;
}

int main() {
    // Load the dataset
    const std::string filename = "val_de_loire_roads.csv";
    std::vector<Road> roads = loadRoads(filename);

    // Create the HTTP server
    httplib::Server svr;

    // Define the endpoint
    svr.Get("/roads", [&](const httplib::Request &req, httplib::Response &res) {
        std::ostringstream response;

        // Respond with the loaded road data in JSON format
        response << "[";
        for (size_t i = 0; i < roads.size(); ++i) {
            response << "{";
            response << "\"landmarkA\":" << roads[i].landmarkA << ",";
            response << "\"landmarkB\":" << roads[i].landmarkB << ",";
            response << "\"time\":" << roads[i].time;
            response << "}";
            if (i < roads.size() - 1) {
                response << ",";
            }
        }
        response << "]";

        res.set_content(response.str(), "application/json");
    });

    std::cout << "Server running on http://localhost:8080/roads" << std::endl;

    // Start the server
    svr.listen("localhost", 8080);

    return 0;
}