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
    Body body1(0.0, 0.0, 0.0, 0.0, 100.0, 1.0);
    Body body2(0.0, 100.0, 1.0, 0.0, 100.0, 1.0);
    Body body3(0.0, 200.0, 0.0, 0.0, 100.0, 1.0);
    Body body4(100.0, 0.0, 0.0, 2.0, 100.0, 1.0);
    Body body5(100.0, 100.0, 0.0, 0.0, 1000.0, 2.0);
    Body body6(100.0, 200.0, 0.0, -3.0, 100.0, 1.0);
    Body body7(200.0, 0.0, 0.0, 0.0, 100.0, 1.0);
    Body body8(200.0, 100.0, -4.0, 0.0, 100.0, 1.0);
    Body body9(200.0, 200.0, 0.0, 0.0, 100.0, 1.0);


    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Body 1: x = " << body1.getX() << ", y = " << body1.getY() << ", mass = " << body1.getMass() << ", radius = " << body1.getRadius() << "\n";
    std::cout << "Body 2: x = " << body2.getX() << ", y = " << body2.getY() << ", mass = " << body2.getMass() << ", radius = " << body2.getRadius() << "\n";
    std::cout << "Body 3: x = " << body3.getX() << ", y = " << body3.getY() << ", mass = " << body3.getMass() << ", radius = " << body3.getRadius() << "\n";
    std::cout << "Body 4: x = " << body4.getX() << ", y = " << body4.getY() << ", mass = " << body4.getMass() << ", radius = " << body4.getRadius() << "\n";
    std::cout << "Body 5: x = " << body5.getX() << ", y = " << body5.getY() << ", mass = " << body5.getMass() << ", radius = " << body5.getRadius() << "\n";
    std::cout << "Body 6: x = " << body6.getX() << ", y = " << body6.getY() << ", mass = " << body6.getMass() << ", radius = " << body6.getRadius() << "\n";
    std::cout << "Body 7: x = " << body7.getX() << ", y = " << body7.getY() << ", mass = " << body7.getMass() << ", radius = " << body7.getRadius() << "\n";
    std::cout << "Body 8: x = " << body8.getX() << ", y = " << body8.getY() << ", mass = " << body8.getMass() << ", radius = " << body8.getRadius() << "\n";
    std::cout << "Body 9: x = " << body9.getX() << ", y = " << body9.getY() << ", mass = " << body9.getMass() << ", radius = " << body9.getRadius() << "\n";

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 50;
    double N = 500;
    double dt = (t_end - t_start) / N;

    // create a system of bodies
    std::vector<Body> bodies;
    bodies.push_back(body1);
    bodies.push_back(body2);
    bodies.push_back(body3);
    bodies.push_back(body4);
    bodies.push_back(body5);
    bodies.push_back(body6);
    bodies.push_back(body7);
    bodies.push_back(body8);
    bodies.push_back(body9);

    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<std::vector<double>>>  trajectories = verlet(bodies, dt, t_end);

    std::cout << "calculated trajectories" << std::endl;

    //Save trajectories using save_Trajectories.hpp
    saveTrajectories(trajectories); 
    
    // (Finish updating)
    return 0;
}