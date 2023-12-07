#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
#include "compute.hpp"
#include "Verlet.hpp"
#include "save_Trajectory.hpp"


int main() {
    // Create two Body objects using different constructors
    Planet planet1(1000.0, 0.0, -10.0, 0.0, 1000.0, 11.0);
    Asteroid asteroid1(0.0, 0.0, 200.0, 0.0, 50.0, 4.0);

    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Planet 1: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";
    std::cout << "Asteroid 1: x = " << asteroid1.getX() << ", y = " << asteroid1.getY() << ", mass = " << asteroid1.getMass() << ", radius = " << asteroid1.getRadius() << "\n";

    // //create a system of bodies
    // std::vector<Body*> system;
    // system.push_back(&planet1);
    // system.push_back(&asteroid1);

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 100;
    double N = 500;
    double dt = (t_end - t_start) / N;

    // create a system of bodies
    std::vector<Body> bodies;
    bodies.push_back(planet1);
    bodies.push_back(asteroid1);
    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<std::vector<double>>>  trajectories = verlet(bodies, dt, t_end);

    std::cout << "calculated trajectories" << std::endl;

    //Save trajectories using save_Tragectories.hpp
    saveTrajectories(trajectories); 
    
    // (Finish updating)
    return 0;
}