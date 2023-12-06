// save_coords.hpp
#ifndef SAVE_COORDS_HPP
#define SAVE_COORDS_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include "body.hpp"

struct Point {
    double x, y;
};

void saveCoordinates(const std::vector<std::vector<double>>& positions, const std::string& filename) {
    // Open a file for writing
    std::ofstream outputFile(filename);

    // Check if the file is open
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return; // or throw an exception
    }

    // Write the header to the CSV file
    outputFile << "X,Y,R" << std::endl;

    // Write each point (x, y) to the CSV file
    for (const auto& row : positions) {
        if (row.size() >= 3) {
            outputFile << row[0] << "," << row[1] << "," << row[2] << std::endl;
        } else {
            std::cerr << "Invalid row in positions vector." << std::endl;
        }
    }

    // Close the file
    outputFile.close();

    std::cout << "Coordinates saved to " << filename << std::endl;
}

#endif // SAVE_COORDS_HPP