/*

The goal of this program is to experiment optimising loading time of a dataset by converting the CSV file to a binary file.

Usage: Compile the program and wait for it to output "CSV data has been converted to binary format.".

Place the CSV file in the quickes_path/data directory and run the program.

Output: The program will output "CSV data has been converted to binary format." to the console and create a binary file in the same directory as the CSV file.

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

// Define a structure to hold road data
struct Road {
    int landmarkA;
    int landmarkB;
    int time;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function Declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to read CSV file and return a vector of Road objects
std::vector<Road> readCSV(const std::string &filename) {

    // Create a container to store all the roads
    std::vector<Road> roads;

    // Open input file for reading
    std::ifstream file(filename);

    // Temporary string to hold each line in the file
    std::string line;

    // For each line in the file
    while (std::getline(file, line)) {

        // Temporary string stream to parse values from line
        std::istringstream ss(line);

        // Temporary variables to hold parsed values
        std::string landmarkA, landmarkB, time;

        // Extract values from the string stream
        std::getline(ss, landmarkA, ',');
        std::getline(ss, landmarkB, ',');
        std::getline(ss, time, ',');

        // Add a Road object to the vector
        roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});
    }

    return roads;
}

// Function to write the vector of Road objects to a binary file
void writeBinary(const std::string &filename, const std::vector<Road> &roads) {

    // Open output file for writing
    std::ofstream file(filename, std::ios::binary);

    // For each road in the vector
    for (const auto &road : roads) {

        // Write the road data to the file
        file.write(reinterpret_cast<const char*>(&road.landmarkA), sizeof(road.landmarkA));
        file.write(reinterpret_cast<const char*>(&road.landmarkB), sizeof(road.landmarkB));
        file.write(reinterpret_cast<const char*>(&road.time), sizeof(road.time));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MAIN
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Read the CSV file
    std::vector<Road> roads = readCSV("../quickest_path/data/USA-roads.csv");

    // Write to a binary file
    writeBinary("optimisedDataset.bin", roads);

    std::cout << "CSV data has been converted to binary format." << std::endl;
    return 0;
}