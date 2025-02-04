#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

struct Road {
    int source;
    int target;
    double weight;
};

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
        if (!std::getline(ss, sourceStr, ',')) continue;
        if (!std::getline(ss, targetStr, ',')) continue;
        if (!std::getline(ss, weightStr, ',')) continue;

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
