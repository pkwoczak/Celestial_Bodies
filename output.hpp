// it is a struct that contains the output of the algorithm
// designed to deal with absorbing bodies
// contains trajectory in vector<vector<vector<double>>> format
// inside vector<vector<double>> is position of all bodies at one time step
// inside vector<double> is position of one body
// outer vector is time
// contains time of collision
// also which bodie absorbed which
#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>

struct output
{
    std::vector<std::vector<std::vector<double>>> trajectory;
    double time;
    std::vector<int> absorbed;
};

#endif      // OUTPUT_HPP