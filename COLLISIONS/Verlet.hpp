#ifndef VERLET_HPP
#define VERLET_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include "body.hpp"

// this deals with the case where the bodies are absorbing
// returns the trajectory in vector<vector<vector<double>>> format
// inside vector<vector<double>> is position of all bodies at one time step
// inside vector<double> is position of one body and its radius (x, y, radius)
// outer vector is time
// the size is nsteps+1*nbodies*3

// create a vector for good_indices that contains the indices of the bodies that are not absorbed

std::vector<std::vector<std::vector<double> > > verlet(std::vector<Body> &bodies, double timeStep, double endTime){
    // number of bodies
    size_t n = bodies.size();
    // dimensions of the bodies
    size_t dim = 2;
    // number of timesteps
    size_t nsteps = endTime / timeStep;

    // initialize the trajectory to be returned
    // trajectory has nsteps+1 vectors, each vector has n elements, each element has 3 elements
    std::vector<std::vector<std::vector<double> > > trajectory(nsteps+1, std::vector<std::vector<double> >(n, std::vector<double>(3)));
    // initialize the trajectory based on the initial positions
    for (size_t i = 0; i < n; i++) {
        trajectory[0][i][0] = bodies[i].getX();
        trajectory[0][i][1] = bodies[i].getY();
        trajectory[0][i][2] = bodies[i].getRadius();
    }
    
    // initialize the positions, velocities, and accelerations
    // size of the vectors is the number of bodies * the number of dimensions
    std::vector<double> positions(n * dim);
    std::vector<double> velocities(n * dim);
    std::vector<double> accelerations(n * dim, 0);
    // initialize the values of the positions, velocities
    for (size_t i = 0; i < n; i++) {
        positions[i * dim] = bodies[i].getX();
        positions[i * dim + 1] = bodies[i].getY();
        velocities[i * dim] = bodies[i].getX_vel();
        velocities[i * dim + 1] = bodies[i].getY_vel();
    }
    
    // initialize the accelerations to by newton's law of gravitation
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i+1; j < n; j++) {
            double distance = bodies[i].calculateDistance(bodies[j]);
            double d = pow(distance, 3);
            accelerations[i * dim] += G * bodies[j].getMass() * (positions[j * dim] - positions[i * dim]) / d;
            accelerations[i * dim + 1] += G * bodies[j].getMass() * (positions[j * dim + 1] - positions[i * dim + 1]) / d;
            accelerations[j * dim] += G * bodies[i].getMass() * (positions[i * dim] - positions[j * dim]) / d;
            accelerations[j * dim + 1] += G * bodies[i].getMass() * (positions[i * dim + 1] - positions[j * dim + 1]) / d;
        }
    }

    // initialize the vector of new accelerations
    std::vector<double> newAccelerations(n * dim);
    // initialize the good_indices vector
    std::vector<int> good_indices(n);
    for (size_t i = 0; i < n; i++){
        good_indices[i] = i;
    }
    
    // loop over the timesteps 
    // bool variable to check if there is any collision
    bool collision = false;
    for (size_t i = 0; i < nsteps; i++) {
        // new position = position + velocity * timeStep + 0.5 * acceleration * timeStep * timeStep
        // iterate over good_indices
        for (size_t j = 0; j < good_indices.size(); j++){
            positions[good_indices[j] * dim] += velocities[good_indices[j] * dim] * timeStep + 0.5 * accelerations[good_indices[j] * dim] * timeStep * timeStep;
            bodies[good_indices[j]].setX(positions[good_indices[j] * dim]);
            positions[good_indices[j] * dim + 1] += velocities[good_indices[j] * dim + 1] * timeStep + 0.5 * accelerations[good_indices[j] * dim + 1] * timeStep * timeStep;
            bodies[good_indices[j]].setY(positions[good_indices[j] * dim + 1]);
        }

        // updated bodies
        // iterate over good_indices
        for (size_t j = 0; j < good_indices.size(); j++) {
            bodies[good_indices[j]].setX(positions[good_indices[j] * dim]);
            bodies[good_indices[j]].setY(positions[good_indices[j] * dim + 1]);
            bodies[good_indices[j]].setX_vel(velocities[good_indices[j] * dim]);
            bodies[good_indices[j]].setY_vel(velocities[good_indices[j] * dim + 1]);
        }

        // update the accelerations
        // initialize the new accelerations to 0
        for (size_t j = 0; j < n; j++) {
            newAccelerations[j * dim] = 0;
            newAccelerations[j * dim + 1] = 0;
        }
        
        // iterate over good_indices
        // and check if there is any collision after finding the distance
        // not break out of the loop if there is a collision, just set collision to true
        for (size_t j = 0; j < good_indices.size(); j++) {
            for (size_t k = j+1; k < good_indices.size(); k++) {
                // compute distance between body j and body k by distance formula in body.hpp
                double distance = bodies[good_indices[j]].calculateDistance(bodies[good_indices[k]]);
                if (bodies[good_indices[j]].isIntersecting(bodies[good_indices[k]])){
                    collision = true;
                }
                double d = pow(distance, 3);
                newAccelerations[good_indices[j] * dim] += G * bodies[good_indices[k]].getMass() * (positions[good_indices[k] * dim] - positions[good_indices[j] * dim]) / d;
                newAccelerations[good_indices[j] * dim + 1] += G * bodies[good_indices[k]].getMass() * (positions[good_indices[k] * dim + 1] - positions[good_indices[j] * dim + 1]) / d;
                newAccelerations[good_indices[k] * dim] += G * bodies[good_indices[j]].getMass() * (positions[good_indices[j] * dim] - positions[good_indices[k] * dim]) / d;
                newAccelerations[good_indices[k] * dim + 1] += G * bodies[good_indices[j]].getMass() * (positions[good_indices[j] * dim + 1] - positions[good_indices[k] * dim + 1]) / d;
            }
        }

        // update the velocities
        // iterate over good_indices
        for (size_t j = 0; j < good_indices.size(); j++) {
            velocities[good_indices[j] * dim] += 0.5 * (accelerations[good_indices[j] * dim] + newAccelerations[good_indices[j] * dim]) * timeStep;
            velocities[good_indices[j] * dim + 1] += 0.5 * (accelerations[good_indices[j] * dim + 1] + newAccelerations[good_indices[j] * dim + 1]) * timeStep;
        }
        
        // update the accelerations
        // iterate over good_indices
        for (size_t j = 0; j < good_indices.size(); j++) {
            accelerations[good_indices[j] * dim] = newAccelerations[good_indices[j] * dim];
            accelerations[good_indices[j] * dim + 1] = newAccelerations[good_indices[j] * dim + 1];
        }
        
        // update the trajectory
        // iterate over every body
        for (size_t j = 0; j < n; j++) {
            trajectory[i + 1][j][0] = positions[j * dim];
            trajectory[i + 1][j][1] = positions[j * dim + 1];
            trajectory[i + 1][j][2] = bodies[j].getRadius();
        }

        // update the good_indices vector if there is a collision
        // since collision is rare, we can brute force it by checking every pair of bodies
        // ignore the efficiency for now
        while (collision){
            collision = false;
            // check the collision between every pair of bodies
            // use absorb function in body.hpp to make code cleaner
            // the body with larger r is the one that absorbs the other bodies (for demonstration purposes)
            // after absorbing, start the loop again
            for (size_t j = 0; j < good_indices.size(); j++){
                for (size_t k = j+1; k < good_indices.size(); k++){
                    if (bodies[good_indices[j]].isIntersecting(bodies[good_indices[k]])){
                        if (bodies[good_indices[j]].getRadius() > bodies[good_indices[k]].getRadius()){
                            bodies[good_indices[j]].absorb(bodies[good_indices[k]]);
                            // erase the smaller body
                            good_indices.erase(good_indices.begin() + k);
                        }
                        else{
                            bodies[good_indices[k]].absorb(bodies[good_indices[j]]);
                            // erase the smaller body
                            good_indices.erase(good_indices.begin() + j);
                        }
                        // start the while loop again
                        collision = true;
                        break;
                    }
                }
                // break out of the loop if there is a collision
                if (collision){
                    break;
                }
            }
            // restart the loop if there is a collision
            if (collision){
                continue;
            }
            // reinitialize the velocities, accelerations
            // size remains the same, just reinitialize the values for the good_indices
            // updated the velocities by bodies
            for (size_t j = 0; j < good_indices.size(); j++) {
                velocities[good_indices[j] * dim] = bodies[good_indices[j]].getX_vel();
                velocities[good_indices[j] * dim + 1] = bodies[good_indices[j]].getY_vel();
                accelerations[good_indices[j] * dim] = 0;
                accelerations[good_indices[j] * dim + 1] = 0;
            }
            
            // initialize the accelerations to by newton's law of gravitation
            for (size_t j = 0; j < good_indices.size(); j++) {
                for (size_t k = j+1; k < good_indices.size(); k++) {
                    double distance = bodies[good_indices[j]].calculateDistance(bodies[good_indices[k]]);
                    double d = pow(distance, 3);
                    accelerations[good_indices[j] * dim] += G * bodies[good_indices[k]].getMass() * (trajectory[i+1][good_indices[k]][0] - trajectory[i+1][good_indices[j]][0]) / d;
                    accelerations[good_indices[j] * dim + 1] += G * bodies[good_indices[k]].getMass() * (trajectory[i+1][good_indices[k]][1] - trajectory[i+1][good_indices[j]][1]) / d;
                    accelerations[good_indices[k] * dim] += G * bodies[good_indices[j]].getMass() * (trajectory[i+1][good_indices[j]][0] - trajectory[i+1][good_indices[k]][0]) / d;
                    accelerations[good_indices[k] * dim + 1] += G * bodies[good_indices[j]].getMass() * (trajectory[i+1][good_indices[j]][1] - trajectory[i+1][good_indices[k]][1]) / d;
                }
            }
        }
    }
    return trajectory;
}

#endif // VERLET_HPP 
