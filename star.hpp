#ifndef STAR_HPP
#define STAR_HPP

#include "body.hpp"

/**
 * @class Star
 * @brief A class that represents a star in a simulation.
 *
 * This class inherits from the Body class and enforces a minimum mass of 10000 and radius of 100.
 */
class Star : public Body {
public:
    // Default constructor
    Star()
        : Body(0, 0, 0, 0, 100, 10000) {}

    // Constructor with all parameters
    Star(double x, double y, double x_vel, double y_vel, double mass, double radius)
        : Body(x, y, x_vel, y_vel, mass, radius) {
            if (mass < 10000) {
                std::cout << "Warning: Input mass is less than 10000. Setting mass to 10000." << std::endl;
                this->setMass(10000);
            }
            if (radius < 100) {
                std::cout << "Warning: Input radius is less than 1000. Setting radius to 100." << std::endl;
                this->setRadius(100);
            }
    }
};

#endif // STAR_HPP