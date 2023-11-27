#include <iostream>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "planet.hpp"
#include "interactions.hpp"
#include "save_coords.hpp"

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
    double t_end = 10;
    double N = 500;
    double dt = (t_end - t_start) / N;

    for (int i=0; i<N; i++){
        //reset the acceleration of each body to 0
        resetAcceleration(system);

        //update the current time
        t = t + dt;

        //calculate the acceleration of each body
        for (int j = 0; j < system.size(); j++) {
            for (int k = j; k < system.size(); k++) {                
                double* force = new double[2];
                force = system[j]->calculateGravityForce(*system[k]);
                
                //update the acceleration of body j
                system[j]->setX_acc(system[j]->getX_acc() + force[0] / system[j]->getMass());
                system[j]->setY_acc(system[j]->getY_acc() + force[1] / system[j]->getMass());
                //update the acceleration of body k
                system[k]->setX_acc(system[k]->getX_acc() - force[0] / system[k]->getMass());
                system[k]->setY_acc(system[k]->getY_acc() - force[1] / system[k]->getMass());
                
                delete[] force;
            }
        }

        //update the velocity of each body
 
        //update the position of each body
    }
    //Testing:
    //create vector of vectors to store the positions and radius of the planets with time
    //positions1 is the vector of vectors for, say, planet 1
    std::vector<std::vector<double> > positions1;
    for(int i = 0; i < N; i++){
        std::vector<double> row;
        row.push_back(3*std::cos(i*dt)); //x
        row.push_back(std::sin(3*i*dt)); //y
        row.push_back(5.0); //radius
        positions1.push_back(row);
    }
    //save positions your planet to a csv file
    saveCoordinates(positions1, "planet1_coordinates.csv");
    
    return 0;
}
