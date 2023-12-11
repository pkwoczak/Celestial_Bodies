
#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>
#include <iostream>
using namespace std;

#define G 1.0

/**
 * @class Body
 * @brief A class that represents a physical body in a simulation.
 *
 * This class contains properties such as position, velocity, acceleration, mass, and radius,
 * and methods to calculate gravity force, check intersection with another body, absorb another body,
 * and calculate elastic collision with another body. Mass and Radius are enforced to be positive.
 */
class Body {
private:
    double x;       // x center coordinate
    double y;       // y center coordinate
    double x_vel;   // velocity in the x direction
    double y_vel;   // velocity in the y direction
    double mass;    // mass of the body
    double radius;   // radius of the body

public:
    //Default constructor
    Body()
        : x(0), y(0), x_vel(0), y_vel(0), mass(1), radius(1) {}


    //Constructor
    Body(double x, double y, double x_vel, double y_vel, double mass, double radius)
        : x(x), y(y), x_vel(x_vel), y_vel(y_vel), mass(mass), radius(radius) {
            if (mass <= 0) {
                std::cout << "Warning: Input mass is non-positive. Setting mass to 1." << std::endl;
                this->mass = 1;
            }
            if (radius <= 0 && radius != -1) {
                std::cout << "Warning: Input radius is non-positive. Setting radius to 1." << std::endl;
                this->radius = 1;
            }
        }

    //Getters
    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getX_vel() const {
        return x_vel;
    }

    double getY_vel() const {
        return y_vel;
    }

    double getMass() const {
        return mass;
    }

    double getRadius() const {
        return radius;
    }

    //Setters
    void setX(double newX) {
        x = newX;
    }

    void setY(double newY) {
        y = newY;
    }

    void setX_vel(double newVelocityX) {
        x_vel = newVelocityX;
    }

    void setY_vel(double newVelocityY) {
        y_vel = newVelocityY;
    }

    void setMass(double newMass) {
        mass = newMass;
    }

    void setRadius(double newRadius) {
        radius = newRadius;
    }

    //Calculate the distance between this body and another body
    double calculateDistance(const Body& otherBody) const {
        return std::sqrt(std::pow(otherBody.getX() - x, 2) + std::pow(otherBody.getY() - y, 2));
    }

    //Calculate the force of gravity exerted from another body
    double* calculateGravityForce(const Body& otherBody) const {
        //calculate the magnitude of the force between the two bodies
        double distance = calculateDistance(otherBody);
        double force = -1.0*(G * mass * otherBody.getMass()) / std::pow(distance, 2);

        //calculate the direction of the force between the two bodies
        //calculate the displacement vector from this body to the other body
        double* displacementVector = new double[2];
        displacementVector[0] = x - otherBody.getX();
        displacementVector[1] = y - otherBody.getY();
        //normalize the displacement vector
        double* forceVector = new double[2];
        forceVector[0] = force * displacementVector[0] / distance;
        forceVector[1] = force * displacementVector[1] / distance;

        // free up the memory allocated for the displacement vector
        delete[] displacementVector;
        return forceVector;
    }

    //Check if this body is currently intersecting another body
    bool isIntersecting(const Body& otherBody) const {
        double distance = calculateDistance(otherBody);
        return distance <= (radius + otherBody.getRadius());
    }

    //Absorb another body into this body
    void absorb(Body& otherBody) {
        //implement absorption with another body
        //inelastic collision
        //update the velocity by conservation of momentum
        x_vel = (mass * x_vel + otherBody.getMass() * otherBody.getX_vel()) / (mass + otherBody.getMass());
        y_vel = (mass * y_vel + otherBody.getMass() * otherBody.getY_vel()) / (mass + otherBody.getMass());
        //update the mass by adding the mass of the other body
        mass += otherBody.getMass();
        //update the radius by r1^3 + r2^3 = (r_final)^3
        radius = std::cbrt(std::pow(radius, 3) + std::pow(otherBody.getRadius(), 3));
        // erase the other body, setting its mass and radius to 0
        otherBody.setMass(0);
        otherBody.setRadius(0);
    }
};

#endif // BODY_HPP
