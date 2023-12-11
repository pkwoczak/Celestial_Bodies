#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
#include "compute.hpp"
#include "Verlet.hpp"
#include "save_Trajectory.hpp"

// Function to generate random positions within the given area
std::pair<double, double> generateRandomPosition(double minX, double maxX, double minY, double maxY) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> disX(minX, maxX);
    std::uniform_real_distribution<double> disY(minY, maxY);
    return {disX(gen), disY(gen)};
}

// Function to check if two bodies overlap
bool checkOverlap(const Body& body1, const Body& body2) {
    return body1.isIntersecting(body2);
}

int main() {
    // Define constants
    const double areaMinX = 0.0;
    const double areaMaxX = 1000.0;
    const double areaMinY = 0.0;
    const double areaMaxY = 1000.0;
    const int numBodies = 20;
    const double minDistance = 10.0;

    // Create vector to store bodies
    std::vector<Body> bodies;

    // Generate random positions for each body, ensuring no overlap
    for (int i = 0; i < numBodies; i++) {
        double x, y;
        bool overlap;
        do {
            std::tie(x, y) = generateRandomPosition(areaMinX, areaMaxX, areaMinY, areaMaxY);
            overlap = false;
            for (const Body& body : bodies) {
                if (checkOverlap(body, Body(x, y, 0.0, 0.0, 100.0, 5.0))) {
                    overlap = true;
                    break;
                }
            }
        } while (overlap);
        bodies.emplace_back(x, y, 0.0, 0.0, 100.0, 5.0);
    }

    // Print initial states
    std::cout << "Initial states:\n";
    for (int i = 0; i < numBodies; i++) {
        const Body& body = bodies[i];
        std::cout << "Body " << i + 1 << ": x = " << body.getX() << ", y = " << body.getY()
                  << ", mass = " << body.getMass() << ", radius = " << body.getRadius() << "\n";
    }

    // Continue with the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 50;
    double N = 500;
    double dt = (t_end - t_start) / N;

    // Calculate the trajectories using the 'verlet' function from Verlet.hpp
    std::vector<std::vector<std::vector<double>>> trajectories = verlet(bodies, dt, t_end);

    // Save trajectories using saveTrajectories function from save_Trajectory.hpp
    saveTrajectories(trajectories);

    return 0;
}