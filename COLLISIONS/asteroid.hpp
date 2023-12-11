#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "body.hpp"

/**
 * @class Asteroid
 * @brief A class that represents a planet in a simulation.
 *
 * This class inherits from the Body class and enforces a minimum mass of 1000 and radius of 10.
 */
class Asteroid : public Body {
public:
    // Default constructor
    Asteroid()
        : Body(0, 0, 0, 0, 1, 10) {}

    // Constructor with all parameters
    Asteroid(double x, double y, double x_vel, double y_vel, double mass, double radius)
        : Body(x, y, x_vel, y_vel, mass, radius) {
            if (mass < 10 || mass >= 100) {
                std::cout << "Warning: Input mass is less than 10 or bigger than 100. Setting mass to 10." << std::endl;
                this->setMass(10);
            }
            if (radius < 1 and radius != -1) {
                std::cout << "Warning: Input radius is less than 1. Setting radius to 1." << std::endl;
                this->setRadius(1);
            }
    }
};

#endif // ASTEROID_HPP