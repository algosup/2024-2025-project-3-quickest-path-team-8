// ‿︵‿୨ Linking ୧‿︵‿

    #include "binary_writer.hpp"
    #include <fstream>
    #include <iostream>


// ‿︵‿୨ Function Definition ୧‿︵‿

    // This function writes a vector of Road objects to a binary file
        void writeBinary(const std::string &filename, const std::vector<Road> &roads) {
            std::ofstream file(filename, std::ios::binary);
            if (!file) {
                std::cerr << "Error: Unable to open binary file for writing: " << filename << std::endl;
                return;
            }

            file.write(reinterpret_cast<const char*>(roads.data()), roads.size() * sizeof(Road));
            if (!file) {
                std::cerr << "Error: Failed to write data to binary file: " << filename << std::endl;
            } else {
                std::cout << "Successfully wrote " << roads.size() << " roads to binary file: " << filename << std::endl;
            }
        }