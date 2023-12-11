#ifndef PLANET_HPP
#define PLANET_HPP

#include "body.hpp"

/**
 * @class Planet
 * @brief A class that represents a planet in a simulation.
 *
 * This class inherits from the Body class and enforces a minimum mass of 1000 and radius of 10.
 */
class Planet : public Body {
public:
    // Default constructor
    Planet()
        : Body(0, 0, 0, 0, 10, 1000) {}

    // Constructor with all parameters
    Planet(double x, double y, double x_vel, double y_vel, double mass, double radius)
        : Body(x, y, x_vel, y_vel, mass, radius) {
            if (mass < 1000 || mass > 10000) {
                std::cout << "Warning: Input mass is less than 1000 or bigger than 10000. Setting mass to 1000." << std::endl;
                this->setMass(1000);
            }
            if (radius < 10 && radius != -1) {
                std::cout << "Warning: Input radius is less than 10. Setting radius to 10." << std::endl;
                this->setRadius(10);
            }
    }
};

#endif // PLANET_HPP