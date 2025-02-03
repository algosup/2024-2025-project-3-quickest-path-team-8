#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>

struct Edge {
    int source;
    int target;
};

std::vector<Edge> readCSV(const std::string& filePath) {
    std::vector<Edge> edges;
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << "\n";
        return edges;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string sourceStr, targetStr;
        if (!std::getline(ss, sourceStr, ',')) continue;
        if (!std::getline(ss, targetStr, ',')) continue;

        try {
            int source = std::stoi(sourceStr);
            int target = std::stoi(targetStr);
            edges.push_back({source, target});
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to parse line: " << line << "\n";
        }
    }

    file.close();
    return edges;
}

void checkConnectivity(const std::vector<Edge>& edges) {
    std::unordered_map<int, std::unordered_set<int>> adjacency;
    for (const auto& edge : edges) {
        adjacency[edge.source].insert(edge.target);
        adjacency[edge.target].insert(edge.source);
    }

    std::unordered_set<int> visited;
    std::vector<std::unordered_set<int>> components;

    for (const auto& node : adjacency) {
        if (visited.find(node.first) == visited.end()) {
            std::queue<int> queue;
            std::unordered_set<int> component;
            queue.push(node.first);
            visited.insert(node.first);
            component.insert(node.first);

            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();

                for (const auto& neighbor : adjacency[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        queue.push(neighbor);
                        component.insert(neighbor);
                    }
                }
            }

            components.push_back(component);
        }
    }

    if (components.size() == 1) {
        std::cout << "All nodes are connected in one main component.\n";
    } else {
        std::cout << "The graph has multiple subgraphs:\n";
        for (size_t i = 0; i < components.size(); ++i) {
            std::cout << "Subgraph " << i + 1 << ": ";
            for (const auto& node : components[i]) {
                std::cout << node << " ";
            }
            std::cout << "\n";
        }
    }
}

int main() {
    std::string filePath = "../data/USA-roads.csv";
    std::vector<Edge> edges = readCSV(filePath);

    if (!edges.empty()) {
        checkConnectivity(edges);
    } else {
        std::cerr << "CSV file must contain 'source' and 'target' columns.\n";
    }

    return 0;
}
