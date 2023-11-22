#ifndef PLANET_HPP
#define PLANET_HPP

#include "body.hpp"

/**
 * @class Planet
 * @brief A class that represents a planet in a simulation.
 *
 * This class inherits from the Body class and enforces a minimum mass and radius of 1000.
 */
class Planet : public Body {
public:
    // Default constructor
    Planet()
        : Body(0, 0, 0, 0, 0, 0, 1000, 1000) {}

    // Constructor with all parameters
    Planet(double x, double y, double x_vel, double y_vel, double x_acc, double y_acc, double mass, double radius)
        : Body(x, y, x_vel, y_vel, x_acc, y_acc, mass, radius) {
            if (mass < 1000) {
                std::cout << "Warning: Input mass is less than 1000. Setting mass to 1000." << std::endl;
                this->setMass(1000);
            }
            if (radius < 1000) {
                std::cout << "Warning: Input radius is less than 1000. Setting radius to 1000." << std::endl;
                this->setRadius(1000);
            }
}
};

#endif // PLANET_HPP