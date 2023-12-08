#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
#include "Verlet.hpp"
#include "save_Trajectory.hpp"

//define pi
const double pi = 3.14159265358979323846;

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int main() {
    // Star star1(0.0, 0.0, 0.0, 0.0, 100000000.0, 100.0); // x, y, vx, vy, mass, radius
    // Planet planet1(400.0, 0.0, 0.0, 500.0, 1000.0, 10.0); // x, y, vx, vy, mass, radius
    Body body1(0,0,0,0,(2*pi)*(2*pi),0.1);
    Body body2(1,0,0,2*pi,0,0.01);

    double t_start = 0;
    double t_end = 1; // Simulation time
    const int planetIndex = 1; // Planet index in bodies vector for analysis

    std::vector<double> min_dist; // Vector to store minimum distances for each N
    
    // Iterate over multiple values of N
    for (int N = 100; N <= 100000000; N *= 10) {

        double dt = (t_end - t_start) / N;
        std::vector<Body> bodies = {body1, body2}; // Reset the bodies for each simulation

        // Calculate the trajectories using Verlet algorithm
        std::vector<std::vector<std::vector<double>>> trajectories = verlet(bodies, dt, t_end);


        double initialX = 1;
        double initialY = 0;

        // Find the minimum distance to last state after simulating
        double curr_metric = calculateDistance(initialX, initialY, trajectories[trajectories.size()-1][planetIndex][0], trajectories[trajectories.size()-1][planetIndex][1]);
        
        min_dist.push_back(curr_metric); // Record the minimum distance for the current N
        std::cout << "N=" << N << ": Minimum distance: " << curr_metric << std::endl;
        
        }
    
    //print min_dist
    std::cout << "Minimum distances: ";
    for (const auto& dist : min_dist) {
        std::cout << dist << " ";
    }
    std::cout << std::endl;

    return 0;
}