#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
#include "save_coords.hpp"
#include "compute.hpp"
#include "Verlet.hpp"
#include "save_Trajectory.hpp"


int main() {
    // Create two Body objects using different constructors
    Star star1(0.0, 0.0, 0.0, 0.0, 100000000.0, 100.0);
    Planet planet1(400.0, 0.0, 0.0, 652.0, 1000.0, 10.0);

    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Star 1: x = " << star1.getX() << ", y = " << star1.getY() << ", mass = " << star1.getMass() << ", radius = " << star1.getRadius() << "\n";
    std::cout << "Star 2: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";

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
    std::vector<std::vector<std::vector<double>>>  trajectories = verlet(bodies, dt, t_end);

    std::cout << "calculated trajectories" << std::endl;

    //Save trajectories using save_Tragectories.hpp
    saveTrajectories(trajectories); 
    
    // (Finish updating)
    return 0;
}
