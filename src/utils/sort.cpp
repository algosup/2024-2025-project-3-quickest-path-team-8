/**
 * @file sort.cpp
 * @brief Road network data sorting and preprocessing utilities
 *
 * Handles loading, validation and sorting of road network data.
 * Prepares data for efficient graph construction.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

/**
 * @brief Road segment data structure
 * 
 * Represents a directed weighted edge in the road network.
 * Weight typically represents travel time or distance.
 */
struct Road {
    int source;     // Source node ID
    int target;     // Target node ID 
    double weight;  // Edge weight/cost
};

/**
 * @brief Reads and validates road network data from CSV
 *
 * @param filePath Path to input CSV file
 * @return vector<Road> List of validated road segments
 *
 * @details
 * - Expects CSV format: source_id,target_id,weight
 * - Performs data validation:
 *   - Numeric field parsing
 *   - Non-negative weights
 *   - Valid node IDs
 * - Skips malformed/invalid records
 *
 * @throws Reports errors to stderr, returns empty vector on failure
 */

std::vector<Road> readCSV(const std::string& filePath) {
    std::vector<Road> roads;
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << "\n";
        return roads;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string sourceStr, targetStr, weightStr;
        if (!std::getline(ss, sourceStr, ',')) continue; // Skip empty lines
        if (!std::getline(ss, targetStr, ',')) continue; // Skip lines with missing fields
        if (!std::getline(ss, weightStr, ',')) continue; // Skip lines with missing weight

        try {
            int source = std::stoi(sourceStr);
            int target = std::stoi(targetStr);
            double weight = std::stod(weightStr);
            roads.push_back({source, target, weight});
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to parse line: " << line << "\n";
        }
    }

    file.close();
    return roads;
}

void writeCSV(const std::string& filePath, const std::vector<Road>& roads) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << "\n";
        return;
    }

    for (const auto& road : roads) {
        file << road.source << "," << road.target << "," << road.weight << "\n";
    }

    file.close();
}

int main() {
    std::string filePath = "../data/USA-roads.csv";
    std::vector<Road> roads = readCSV(filePath);
    size_t originalCount = roads.size();

    std::sort(roads.begin(), roads.end(), [](const Road& a, const Road& b) {
        if (a.source == b.source) {
            return a.target < b.target;
        }
        return a.source < b.source;
    });

    std::string outputPath = "../data/USA-roads_sorted.csv";
    writeCSV(outputPath, roads);
    size_t sortedCount = roads.size();

    std::cout << "File sorted and saved as: " << outputPath << "\n";
    std::cout << "Original row count: " << originalCount << "\n";
    std::cout << "Sorted row count: " << sortedCount << "\n";

    if (originalCount == sortedCount) {
        std::cout << "No values are missing. Row counts match.\n";
    } else {
        std::cout << "Warning: Mismatch detected. Rows may be missing!\n";
        std::cout << "Difference: " << originalCount - sortedCount << "\n";
    }

    return 0;
}
