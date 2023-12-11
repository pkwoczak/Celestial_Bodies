#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "star.hpp"
#include "asteroid.hpp"
//#include "compute.hpp"
#include "Verlet.hpp"
#include "save_Trajectory.hpp"
const double pi = 3.14159265358979323846;

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int main() {
    // Create two Body objects using different constructors
    // Star star1(0.0, 0.0, 0.0, 0.0, 100000000.0, 100.0); // x, y, vx, vy, mass, radius

    

    // Planet planet1(400.0, 0.0, 0.0, 500.0, 1000.0, 10.0); // x, y, vx, vy, mass, radius
    
    // // Print initial states
    // std::cout << "Initial states:\n";
    // std::cout << "Star: x = " << star1.getX() << ", y = " << star1.getY() << ", mass = " << star1.getMass() << ", radius = " << star1.getRadius() << "\n";
    // std::cout << "Planet: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";

    // //create a system of bodies
    // std::vector<Body*> system;
    // system.push_back(&star1);
    // system.push_back(&planet1);
    Body body1(0,0,0,0,(2*pi)*(2*pi),0.1);
    Body body2(1,0,0,2*pi,0,0.01); 

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 2;
    double N = 100; 
    double dt = (t_end - t_start) / N;


    // create a system of bodies
    std::vector<Body> bodies;
    bodies.push_back(body1);
    bodies.push_back(body2);
    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<std::vector<double>>>  trajectories = verlet(bodies, dt, t_end);

    std::cout << "calculated trajectories" << std::endl;

    //Save trajectories using save_Tragectories.hpp
    saveTrajectories(trajectories); 
    
    return 0;
}