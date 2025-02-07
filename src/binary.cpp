// g++ -std=c++17 -O1 -march=native "binary.cpp" -o binary && ./binary

#include "includes/binary.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// Function to convert CSV to binary
void convertCSVtoBinary(const std::string& csvFilename, const std::string& binaryFilename) {
    // Open the CSV file for reading
    std::ifstream csvFile(csvFilename);
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << csvFilename << std::endl;
        return;
    }

    // Open the binary file for writing
    std::ofstream binaryFile(binaryFilename, std::ios::binary);
    if (!binaryFile.is_open()) {
        std::cerr << "Error: Could not open binary file for writing: " << binaryFilename << std::endl;
        return;
    }

    std::string line;
    Road road;
    char comma; // To handle the commas in the CSV

    // Read the CSV file line by line
    while (getline(csvFile, line)) {
        std::stringstream ss(line);
        // Parse the line: landmarkA,landmarkB,time
        ss >> road.landmarkA >> comma >> road.landmarkB >> comma >> road.time;

        // Write the Road structure to the binary file
        binaryFile.write(reinterpret_cast<const char*>(&road), sizeof(Road));
    }

    // Close the files
    csvFile.close();
    binaryFile.close();

    std::cout << "Successfully converted CSV file to binary format: " << binaryFilename << std::endl;
}

