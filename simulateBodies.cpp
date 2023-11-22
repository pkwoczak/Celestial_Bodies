#include <iostream>
#include "body.hpp"
#include "planet.hpp"

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


    
    return 0;
}