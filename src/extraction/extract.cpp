/*

The goal of this program is to experiment optimising loading time of a dataset by converting the CSV file to a binary file.

Usage: Compile the program and wait for it to output "CSV data has been converted to binary format.".

Place the CSV file in the quickest_path/data directory and run the program.

Output: The program will output "CSV data has been converted to binary format." to the console and create a binary file in the same directory as the CSV file.

TODO: If the size of the dataset is known and fixed, std::array<Road, N> could be considered for further optimization.

*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Linking Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definition Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Global Declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ensure the structure is packed tightly without padding
#pragma pack(push, 1)
struct Road {
    int landmarkA;
    int landmarkB;
    int time;
};
#pragma pack(pop)

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function Declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to read CSV file and return a vector of Road objects
std::vector<Road> readCSV(const std::string &filename) {
    std::vector<Road> roads;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open CSV file " << filename << std::endl;
        return roads;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string landmarkA, landmarkB, time;
        if (std::getline(ss, landmarkA, ',') &&
            std::getline(ss, landmarkB, ',') &&
            std::getline(ss, time, ',')) {
            roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});
        } else {
            std::cerr << "Error: Malformed line in CSV file: " << line << std::endl;
        }
    }

    if (roads.empty()) {
        std::cerr << "Error: No data read from CSV file " << filename << std::endl;
    } else {
        std::cout << "Successfully read " << roads.size() << " roads from CSV file: " << filename << std::endl;
    }

    return roads;
}

// Function to write the vector of Road objects to a binary file
void writeBinary(const std::string &filename, const std::vector<Road> &roads) {
    // Open output file for writing
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open binary file for writing: " << filename << std::endl;
        return;
    }

    // Write the entire vector to the file
    file.write(reinterpret_cast<const char*>(roads.data()), roads.size() * sizeof(Road));
    if (!file) {
        std::cerr << "Error: Failed to write data to binary file: " << filename << std::endl;
    } else {
        std::cout << "Successfully wrote " << roads.size() << " roads to binary file: " << filename << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MAIN
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();
    
    // Read the CSV file
    std::vector<Road> roads = readCSV("../../quickest_path/data/USA-roads.csv");

    // Write to a binary file
    writeBinary("../data/extractedDataset.bin", roads);

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Output the time taken
    std::cout << "Time taken for extraction: " << duration.count() << " seconds" << std::endl;
    std::cout << "CSV data has been converted to binary format." << std::endl;
    return 0;
}