
#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>

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
    double x_acc;   // acceleration in the x direction
    double y_acc;   // acceleration in the y direction
    double mass;    // mass of the body
    double radius;   // radius of the body

public:
    //Default constructor
    Body()
        : x(0), y(0), x_vel(0), y_vel(0), x_acc(0), y_acc(0), mass(1), radius(1) {}


    //Constructor
    Body(double x, double y, double x_vel, double y_vel, double x_acc, double y_acc, double mass, double radius)
        : x(x), y(y), x_vel(x_vel), y_vel(y_vel), x_acc(x_acc), y_acc(y_acc), mass(mass), radius(radius) {
            if (mass <= 0) {
                std::cout << "Warning: Input mass is non-positive. Setting mass to 1." << std::endl;
                this->mass = 1;
            }
            if (radius <= 0) {
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

    double getX_acc() const {
        return x_acc;
    }

    double getY_acc() const {
        return y_acc;
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

    void setX_acc(double newAccelerationX) {
        x_acc = newAccelerationX;
    }

    void setY_acc(double newAccelerationY) {
        y_acc = newAccelerationY;
    }

    void setMass(double newMass) {
        mass = newMass;
    }

    void setRadius(double newRadius) {
        radius = newRadius;
    }

    //Calculate the force of gravity exerted from another body
    double* calculateGravityForce(const Body& otherBody) const {
        //calculate the magnitude of the force between the two bodies
        double distance = std::sqrt(std::pow(otherBody.getX() - x, 2) + std::pow(otherBody.getY() - y, 2));
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
        double distance = std::sqrt(std::pow(otherBody.getX() - x, 2) + std::pow(otherBody.getY() - y, 2));
        return distance <= (radius + otherBody.getRadius());
    }

    //Absorb another body into this body
    void absorb(Body& otherBody) {
        //implement absorption with another body
        //updates mass, radius, and velocity and acceleration following
        //inelastic collision


    }

    //Calculate elastic collision with another body
    void calculateElasticCollision(Body& otherBody) {
    //implement elastic collision

    }
};

#endif // BODY_HPP
