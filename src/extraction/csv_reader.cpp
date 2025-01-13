// ‿︵‿୨ Linking ୧‿︵‿

    #include "csv_reader.hpp"
    #include <fstream>
    #include <sstream>
    #include <iostream>

// ‿︵‿୨ Function Definition ୧‿︵‿

    // This function reads a CSV file and returns a vector of Road objects
        std::vector<Road> readCSV(const std::string &filename) {
            
            // Create a vector to store the roads
            std::vector<Road> roads;

            // Open the CSV file
            std::ifstream file(filename);
            if (!file) {

                // Print an error message if the file cannot be opened
                std::cerr << "Error: Unable to open CSV file " << filename << std::endl;
                return roads;
            }

            // Instantiate a string to store each line of the CSV file
            std::string line;

            // For each line in the file:
            while (std::getline(file, line)) {

                // Create a string stream to parse the line
                std::istringstream ss(line);

                // Parse the line into three strings representing the two landmarks and the time
                std::string landmarkA, landmarkB, time;

                // If the line contains three values separated by commas:
                if (std::getline(ss, landmarkA, ',') && std::getline(ss, landmarkB, ',') && std::getline(ss, time, ',')) {

                        // Create a Road object and add it to the vector
                        roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});

                    // Otherwise, print an error message
                    } else {
                        std::cerr << "Error: Malformed line in CSV file: " << line << std::endl;
                    }
            }

            // Print a message if no data was read from the file
            if (roads.empty()) {
                std::cerr << "Error: No data read from CSV file " << filename << std::endl;
            
            // Otherwise, print a message indicating the number of roads read
            } else {
                std::cout << "Successfully read " << roads.size() << " roads from CSV file: " << filename << std::endl;
            }

            return roads;
        }