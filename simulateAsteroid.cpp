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
    Planet planet1(0.0, 0.0, 0.0, 0.0, 5000.0, 50.0);
    Asteroid asteroid1(0.0, -100.0, 10.0, 10.0, 10.0, 1.0);

    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Star 1: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";
    std::cout << "Asteroid 1: x = " << asteroid1.getX() << ", y = " << asteroid1.getY() << ", mass = " << asteroid1.getMass() << ", radius = " << asteroid1.getRadius() << "\n";

    // //create a system of bodies
    // std::vector<Body*> system;
    // system.push_back(&planet1);
    // system.push_back(&planet1);

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 100;
    double N = 700;
    double dt = (t_end - t_start) / N;

    // create a system of bodies
    std::vector<Body> bodies;
    bodies.push_back(planet1);
    bodies.push_back(asteroid1);
    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<double>> trajectories = compute(bodies, dt, t_end);

    // Transform the computed trajectories into position vectors with time and radius for each body
    std::vector<std::vector<double>> positions_planet1, positions_asteroid1;

    for (const auto& step : trajectories) {
        std::vector<double> pos1;
        pos1.push_back(step[0]);
        pos1.push_back(step[1]);
        pos1.push_back(bodies[0].getRadius());

        std::vector<double> pos2;
        pos2.push_back(step[2]);
        pos2.push_back(step[3]);
        pos2.push_back(bodies[1].getRadius());

        positions_planet1.push_back(pos1);
        positions_asteroid1.push_back(pos2);
    }
    std::cout << "calculated trajectories" << std::endl;

    // Save the positions of each body to separate CSV files
    saveCoordinates(positions_planet1, "coords/planet1_coordinates.csv");
    saveCoordinates(positions_asteroid1, "coords/asteroid1_coordinates.csv");
    
    // (Finish updating)
    return 0;
}
