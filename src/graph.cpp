#include "includes/binary.hpp"
#include "includes/graph.hpp"

#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void Graph::loadGraphFromBinary(const std::string& filename) {

    // Memory-map the binary file
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    size_t fileSize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    Road* roads = static_cast<Road*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
    size_t numRecords = fileSize / sizeof(Road);

    // Pre-allocate vectors with known sizes
    edges.reserve(numRecords * 2); // Graph is bidirectional
    id_map.reserve(numRecords * 2);

    // Phase 1: Create ID mapping
    std::unordered_map<int, int> temp_id_map;
    for (size_t i = 0; i < numRecords; ++i) {
        insertIfNew(roads[i].landmarkA, temp_id_map);
        insertIfNew(roads[i].landmarkB, temp_id_map);
    }
    
    // Convert to contiguous IDs (0-based)
    id_map.reserve(temp_id_map.size());
    reverse_id_map.reserve(temp_id_map.size());
    for (const auto& pair : temp_id_map) {
        id_map[pair.first] = static_cast<int>(reverse_id_map.size());
        reverse_id_map.push_back(pair.first);
    }

    // Phase 2: Calculate degrees
    degrees.resize(id_map.size(), 0);
    for (size_t i = 0; i < numRecords; ++i) {
        int a = id_map[roads[i].landmarkA];
        int b = id_map[roads[i].landmarkB];
        degrees[a]++;
        degrees[b]++;
    }

    // Phase 3: Build CSR offsets
    offsets.resize(id_map.size() + 1);
    offsets[0] = 0;
    for (size_t i = 0; i < id_map.size(); ++i) {
        offsets[i + 1] = offsets[i] + degrees[i];
        degrees[i] = 0; // Reset for next phase
    }

    // Phase 4: Populate edges (bidirectional)
    edges.resize(offsets.back());
    for (size_t i = 0; i < numRecords; ++i) {
        int a = id_map[roads[i].landmarkA];
        int b = id_map[roads[i].landmarkB];
        int time = roads[i].time;

        // Add both directions
        addEdgeCSR(a, b, time);
        addEdgeCSR(b, a, time);
    }

    munmap(roads, fileSize);
    close(fd);
    std::cout << "Loaded graph with " << id_map.size() 
              << " nodes and " << edges.size() << " edges\n";
}

void Graph::insertIfNew(int landmark, std::unordered_map<int, int>& temp_map) {
    if (temp_map.find(landmark) == temp_map.end()) {
        temp_map[landmark] = static_cast<int>(temp_map.size());
    }
}

void Graph::addEdgeCSR(int src, int dest, int time) {
    size_t pos = offsets[src] + degrees[src];
    edges[pos] = {dest, time};
    degrees[src]++;
}

// Accessor implementations
const std::vector<Edge>& Graph::getEdges() const {
    return edges;
}

const std::vector<size_t>& Graph::getOffsets() const {
    return offsets;
}

int Graph::getMappedId(int original_id) const {
    return id_map.at(original_id);
}

int Graph::getOriginalId(int mapped_id) const {
    return reverse_id_map[mapped_id];
}