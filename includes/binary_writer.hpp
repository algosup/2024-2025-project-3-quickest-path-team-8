// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef BINARY_WRITER_H
    #define BINARY_WRITER_H

    #include <vector>
    #include <string>
    #include "csv_reader.hpp"


// ‿︵‿୨ Function Definition ୧‿︵‿

    /**
     * @brief Write the roads to a binary file
     * 
     * @param filename The name of the file to write to
     * @param roads The roads to write
     */
    void writeBinary(const std::string &filename, const std::vector<Road> &roads);

    #endif // BINARY_WRITER_H