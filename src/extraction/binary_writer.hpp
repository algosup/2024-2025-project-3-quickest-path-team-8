// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef BINARY_WRITER_H
    #define BINARY_WRITER_H

    #include <vector>
    #include <string>
    #include "csv_reader.hpp"


// ‿︵‿୨ Function Definition ୧‿︵‿

    // This function writes a vector of Road objects to a binary file
        void writeBinary(const std::string &filename, const std::vector<Road> &roads);

    #endif // BINARY_WRITER_H