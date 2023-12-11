#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
#include "save_coords.hpp"
#include "compute.hpp"

int main() {
    // Create two Body objects using different constructors
    Star star1(0.0, 0.0, 0.0, 0.0, 100000000.0, 100.0);
    Planet planet1(400.0, 0.0, 0.0, 500.0, 1000.0, 10.0);

    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Star 1: x = " << star1.getX() << ", y = " << star1.getY() << ", mass = " << star1.getMass() << ", radius = " << star1.getRadius() << "\n";
    std::cout << "Planet 1: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";

    // //create a system of bodies
    // std::vector<Body*> system;
    // system.push_back(&star1);
    // system.push_back(&planet1);

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 100;
    double N = 500;
    double dt = (t_end - t_start) / N;

    // create a system of bodies
    std::vector<Body> bodies;
    bodies.push_back(star1);
    bodies.push_back(planet1);
    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<double>> trajectories = compute(bodies, dt, t_end);

    // Transform the computed trajectories into position vectors with time and radius for each body
    std::vector<std::vector<double>> positions_star1, positions_planet1;

    for (const auto& step : trajectories) {
        std::vector<double> pos1;
        pos1.push_back(step[0]);
        pos1.push_back(step[1]);
        pos1.push_back(bodies[0].getRadius());

        std::vector<double> pos2;
        pos2.push_back(step[2]);
        pos2.push_back(step[3]);
        pos2.push_back(bodies[1].getRadius());

        positions_star1.push_back(pos1);
        positions_planet1.push_back(pos2);
    }
    std::cout << "calculated trajectories" << std::endl;

    // Save the positions of each body to separate CSV files
    saveCoordinates(positions_star1, "coords/star1_coordinates.csv");
    saveCoordinates(positions_planet1, "coords/planet1_coordinates.csv");
    
    // (Finish updating)
    return 0;
}
