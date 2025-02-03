#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

// Road structure for binary file storage
#pragma pack(push, 1)
struct Road {
    int32_t landmarkA; // Starting node
    int32_t landmarkB; // Ending node
    int16_t time;      // Travel time
};
#pragma pack(pop)

// Function to convert CSV to binary
void convertCSVtoBinary(const string& csvFilename, const string& binaryFilename) {
    // Open the CSV file for reading
    ifstream csvFile(csvFilename);
    if (!csvFile.is_open()) {
        cerr << "Error: Could not open CSV file: " << csvFilename << endl;
        return;
    }

    // Open the binary file for writing
    ofstream binaryFile(binaryFilename, ios::binary);
    if (!binaryFile.is_open()) {
        cerr << "Error: Could not open binary file for writing: " << binaryFilename << endl;
        return;
    }

    string line;
    Road road;
    char comma; // To handle the commas in the CSV

    // Read the CSV file line by line
    while (getline(csvFile, line)) {
        stringstream ss(line);
        // Parse the line: landmarkA,landmarkB,time
        ss >> road.landmarkA >> comma >> road.landmarkB >> comma >> road.time;

        // Write the Road structure to the binary file
        binaryFile.write(reinterpret_cast<const char*>(&road), sizeof(Road));
    }

    // Close the files
    csvFile.close();
    binaryFile.close();

    cout << "Successfully converted CSV file to binary format: " << binaryFilename << endl;
}

int main() {
    // Convert CSV to binary
    convertCSVtoBinary("../../data/USA-roads_sorted.csv", "graph_data.bin");

    return 0;
}