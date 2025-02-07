#ifndef BINARY_HPP
#define BINARY_HPP

#include <string>
#include <cstdint>
/// @brief Road structure for binary file storage (pragma pack to minimize memory padding)
#pragma pack(push, 1)
struct Road {

    /// @brief Starting node
    int32_t landmarkA;

    /// @brief Ending node
    int32_t landmarkB;
    
    /// @brief Travel time
    int16_t time;
};
#pragma pack(pop)

/// @brief This function converts a CSV file to a binary file
/// @param csvFilename is the name of the CSV file
/// @param binaryFilename is the name of the binary file
/// @note The CSV file should have the format: landmarkA,landmarkB,time
/// @return void
void convertCSVtoBinary(const std::string& csvFilename, const std::string& binaryFilename);

#endif // BINARY_HPP