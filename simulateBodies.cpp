#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "interactions.hpp"
#include "save_coords.hpp"
#include "compute.hpp"

int main() {
    // Create two Body objects using different constructors
    Body body1;
    Body body2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, -1.0);

    // Print initial states
    std::cout << "Initial states:\n";
    std::cout << "Body 1: x = " << body1.getX() << ", y = " << body1.getY() << ", mass = " << body1.getMass() << ", radius = " << body1.getRadius() << "\n";
    std::cout << "Body 2: x = " << body2.getX() << ", y = " << body2.getY() << ", mass = " << body2.getMass() << ", radius = " << body2.getRadius() << "\n";

    // Test setters
    body1.setX(10.0);
    body1.setY(20.0);
    body1.setMass(30.0);
    body1.setRadius(40.0);

    // Print states after using setters
    std::cout << "\nAfter using setters:\n";
    std::cout << "Body 1: x = " << body1.getX() << ", y = " << body1.getY() << ", mass = " << body1.getMass() << ", radius = " << body1.getRadius() << "\n";

    // Test isIntersecting
    bool intersecting = body1.isIntersecting(body2);
    std::cout << "\nAre the bodies intersecting? " << (intersecting ? "Yes" : "No") << "\n\n";

    // Test isIntersecting after changing radius of body1
    body1.setRadius(2.0);
    intersecting = body1.isIntersecting(body2);
    std::cout << "Body 1: x = " << body1.getX() << ", y = " << body1.getY() << ", mass = " << body1.getMass() << ", radius = " << body1.getRadius() << "\n";
    std::cout << "\nAre the bodies intersecting? " << (intersecting ? "Yes" : "No") << "\n";

    //Planet tests
    Planet planet1;
    Planet planet2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 100, 314); //bad

    //print states 
    std::cout << "Initial states:\n";
    std::cout << "Planet 1: x = " << planet1.getX() << ", y = " << planet1.getY() << ", mass = " << planet1.getMass() << ", radius = " << planet1.getRadius() << "\n";
    std::cout << "Planet 2: x = " << planet2.getX() << ", y = " << planet2.getY() << ", mass = " << planet2.getMass() << ", radius = " << planet2.getRadius() << "\n";

    //see if planets intersect
    intersecting = planet1.isIntersecting(planet2);
    std::cout << "\nAre the planets intersecting? " << (intersecting ? "Yes" : "No") << "\n\n";

    //test the gravitational force
    Planet planet3(0, 0, 0, 0, 0, 0, 1000, 1000);
    Planet planet4(0, 1000, 0, 0, 0, 0, 1000, 1000);
    double* force = new double[2];
    force = planet3.calculateGravityForce(planet4);
    std::cout << "The mass of planet 3 is " << planet3.getMass() << "\n";
    std::cout << "The mass of planet 4 is " << planet4.getMass() << "\n";
    std::cout << "The distance between planet 3 and planet 4 is " << std::sqrt(std::pow(planet3.getX() - planet4.getX(), 2) + std::pow(planet3.getY() - planet4.getY(), 2)) << "\n";
    std::cout << "The force on planet 3 from planet 4 is: " << force[0] << ", " << force[1] << "\n";
    delete [] force;

    //create a system of bodies
    std::vector<Body*> system;
    system.push_back(&planet3);
    system.push_back(&planet4);
    
    //print the system
    std::cout << "\n\nThe system is: \n";
    for (int i = 0; i < system.size(); i++) {
        std::cout << "Body " << i << ": x = " << system[i]->getX() << ", y = " << system[i]->getY() << ", mass = " << system[i]->getMass() << ", radius = " << system[i]->getRadius() << "\n";
    }

    //conduct the simulation
    double t_start = 0;
    double t = t_start;
    double t_end = 20;
    double N = 500;
    double dt = (t_end - t_start) / N;

    //set masses and radii for the bodies
    body1.setMass(3.0);
    body1.setRadius(1.0);
    body1.setX(0.3);
    body1.setY(0);
    body1.setX_vel(0);
    body1.setY_vel(-1);
    body2.setMass(3.0);
    body2.setRadius(1.0);
    body2.setX(-0.3);
    body2.setY(0);
    body2.setX_vel(0);
    body2.setY_vel(-5);

    std::vector<Body> bodies = {body1, body2};
    std::cout << "created bodies" << std::endl;
    //calculate the trajectory of each body here 
    // Calculate the trajectories using the 'compute' function from compute.hpp
    std::vector<std::vector<double>> trajectories = compute(bodies, dt, t_end);

    // Transform the computed trajectories into position vectors with time and radius for each body
    std::vector<std::vector<double>> positions_body1, positions_body2;

    for (const auto& step : trajectories) {
        std::vector<double> pos1 = {step[0], step[1], bodies[0].getRadius()};
        std::vector<double> pos2 = {step[2], step[3], bodies[1].getRadius()};
        positions_body1.push_back(pos1);
        positions_body2.push_back(pos2);
    }
    std::cout << "calculated trajectories" << std::endl;

    // Save the positions of each body to separate CSV files
    saveCoordinates(positions_body1, "coords/body1_coordinates.csv");
    saveCoordinates(positions_body2, "coords/body2_coordinates.csv");
    
    // (Finish updating)
    return 0;
}
