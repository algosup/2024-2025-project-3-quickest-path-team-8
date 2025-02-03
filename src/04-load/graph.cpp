#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

struct Edge {
    int32_t destination;
    int32_t travel_time;
} __attribute__((packed));

#pragma pack(push, 1)
struct Road {
    int32_t landmarkA;
    int32_t landmarkB;
    int16_t time;
};
#pragma pack(pop)



class Graph {
public:
    // CSR structure
    alignas(64) vector<Edge> edges;
    alignas(64) vector<size_t> offsets;
    vector<int> degrees;
    unordered_map<int, int> id_map;  // Maps original IDs to contiguous indices
    vector<int> reverse_id_map;      // Maps contiguous indices back to original IDs
    
    void loadGraphFromBinary(const string& filename) {
        // Memory-map the binary file
        int fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        
        size_t fileSize = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        Road* roads = static_cast<Road*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
        size_t numRecords = fileSize / sizeof(Road);

        // Pre-allocate vectors with known sizes
        edges.reserve(numRecords * 2); // Since graph is bidirectional
        id_map.reserve(numRecords * 2);
        
        // Use larger read chunks
        const size_t CHUNK_SIZE = 8192;
        char* buffer = new char[CHUNK_SIZE];

        // Phase 1: Create ID mapping
        unordered_map<int, int> temp_id_map;
        for (size_t i = 0; i < numRecords; ++i) {
            insertIfNew(roads[i].landmarkA, temp_id_map);
            insertIfNew(roads[i].landmarkB, temp_id_map);
        }
        
        // Convert to contiguous IDs (0-based)
        id_map.reserve(temp_id_map.size());
        reverse_id_map.reserve(temp_id_map.size());  // Reserve space only
        for (const auto& pair : temp_id_map) {
            id_map[pair.first] = reverse_id_map.size();  // Assign 0-based IDs
            reverse_id_map.push_back(pair.first);        // Build reverse map
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
            offsets[i+1] = offsets[i] + degrees[i];
            degrees[i] = 0;  // Reset for next phase
        }

        // Phase 4: Populate edges (bidirectional)
        edges.resize(offsets.back());
        for (size_t i = 0; i < numRecords; ++i) {
            int a = id_map[roads[i].landmarkA];
            int b = id_map[roads[i].landmarkB];
            int time = roads[i].time;

            if (a >= degrees.size() || b >= degrees.size()) {
                cerr << "Invalid node ID in edge: " << roads[i].landmarkA 
                    << " or " << roads[i].landmarkB << endl;
                exit(1);
            }


            // Add both directions
            addEdgeCSR(a, b, time);
            addEdgeCSR(b, a, time);
        }

        munmap(roads, fileSize);
        close(fd);
        cout << "Loaded graph with " << id_map.size() << " nodes and " 
             << edges.size() << " edges\n";
    }

private:
    void insertIfNew(int landmark, unordered_map<int, int>& temp_map) {
        if (temp_map.find(landmark) == temp_map.end()) {
            temp_map[landmark] = temp_map.size();
        }
    }

    void addEdgeCSR(int src, int dest, int time) {
        size_t pos = offsets[src] + degrees[src];
        edges[pos] = {dest, time};
        degrees[src]++;
    }

public:
    // Accessors for CSR data
    const vector<Edge>& getEdges() const { return edges; }
    const vector<size_t>& getOffsets() const { return offsets; }
    int getMappedId(int original_id) const { return id_map.at(original_id); }
    int getOriginalId(int mapped_id) const { return reverse_id_map[mapped_id]; }
};