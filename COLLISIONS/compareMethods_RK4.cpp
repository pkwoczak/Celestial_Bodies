#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "RK4.hpp"
#include "RK4.hpp"
#include "save_Trajectory.hpp"

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}
//define pi
const double pi = 3.14159265358979323846;

int main() {
    // Initialize your celestial bodies
    // Star star1(0.0, 0.0, 0.0, 0.0, 100000000.0, 100.0); // x, y, vx, vy, mass, radius
    // Planet planet1(400.0, 0.0, 0.0, 500.0, 1000.0, 10.0); // x, y, vx, vy, mass, radius
    Body body1(0,0,0,0,(2*pi)*(2*pi),0.1);
    Body body2(1,0,0,2*pi,0.0001,0.01);
    double t_start = 0;
    double t_end = 1; // Simulation time
    const int planetIndex = 1; // Planet index in bodies vector for analysis, multiplied by dim (which is 2)

    std::vector<double> min_dist; // Vector to store minimum distances for each N
    
    // Iterate over multiple values of N
    for (int N = 2; N <= 2; N *= 10) {
    double dt = (t_end - t_start) / N;
    std::vector<Body> bodies = {body1, body2}; // Reset the bodies for each simulation

    // Calculate the trajectories using RK4 algorithm
    std::vector<std::vector<double>> trajectory = RK4(bodies, dt, t_end);

    // Print the trajectories of the indexed planet to check
    size_t dim = 2; // Assuming 2D space as in initial code
    size_t n = bodies.size(); // Number of bodies
    int planetIndexCorrected = planetIndex * dim * n; // Correct indexing offset

    for (const auto& state : trajectory) {
        std::cout << "x: " << state[planetIndexCorrected] << ", y: " << state[planetIndexCorrected + 1] << std::endl;
    }

    double initialX = 1;
    double initialY = 0;
    double curr_min = 1000000;

    // Find the minimum distance to the initial state after simulating
    for (size_t step = 0; step < trajectory.size(); step++) {
        double curr_x = trajectory[step][planetIndexCorrected];
        double curr_y = trajectory[step][planetIndexCorrected + 1];

        double distance = calculateDistance(initialX, initialY, curr_x, curr_y);
        if (distance < curr_min) {
            curr_min = distance;
        }
    }

    min_dist.push_back(curr_min); // Record the minimum distance for the current N
    std::cout << "N=" << N << ": Minimum distance: " << curr_min << std::endl;
}

    
    return 0;
}