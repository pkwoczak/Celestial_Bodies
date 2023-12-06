#ifndef compute_hpp
#define compute_hpp

#include <cmath>
#include <iostream>
#include <vector>
#include "body.hpp"

std::vector<std::vector<double> > compute(std::vector<Body> &bodies, double timeStep, double endTime){
    std::cout << "Computing trajectory...\n";
    // number of bodies
    size_t n = bodies.size();
    // dimensions of the bodies 
    size_t dim = 2;
    // number of timesteps
    size_t nsteps = endTime / timeStep;
    
    // record the trajectory(with time) of the bodies
    // trajectory has nsteps vectors, each vector has n*dim elements
    std::vector<std::vector<double> > trajectory(nsteps+1, std::vector<double>(n * dim));
    // initialize the trajectory based on the initial positions
    for (size_t i = 0; i < n; i++) {
        trajectory[0][i * dim] = bodies[i].getX();
        trajectory[0][i * dim + 1] = bodies[i].getY();
    }

    // initialize the positions, velocities, and accelerations
    // size of the vectors is the number of bodies * the number of dimensions
    std::vector<double> positions(n * dim);
    std::vector<double> velocities(n * dim);
    std::vector<double> accelerations(n * dim, 0);
    
    // initialize the values of the positions, velocities, and accelerations
    for (size_t i = 0; i < n; i++) {
        positions[i * dim] = bodies[i].getX();
        positions[i * dim + 1] = bodies[i].getY();
        velocities[i * dim] = bodies[i].getX_vel();
        velocities[i * dim + 1] = bodies[i].getY_vel();
    }
    
    std::cout << "Initialized positions, velocities, and accelerations\n";
    
    // loop over the timesteps
    // new position = position + velocity * timestep + 0.5 * acceleration * timestep^2
    // update the accelerations using the new positions by newton's law of gravitation
    // new acceleration = G * mass / distance^2
    // initialize the vector of new accelerations
    std::vector<double> newAccelerations(n * dim);
    // new velocity = velocity + (acceleration + new accerleration) * timestep *0.5
    for (size_t i = 0; i < nsteps; i++) {
        // update the positions
        for (size_t j = 0; j < n; j++) {
            positions[j * dim] += velocities[j * dim] * timeStep + 0.5 * accelerations[j * dim] * timeStep * timeStep;
            bodies[j].setX(positions[j * dim]);
            positions[j * dim + 1] += velocities[j * dim + 1] * timeStep + 0.5 * accelerations[j * dim + 1] * timeStep * timeStep;
            bodies[j].setY(positions[j * dim + 1]);
        }
        // update the accelerations
        // initialize the new accelerations to 0
        for (size_t j = 0; j < n; j++) {
            newAccelerations[j * dim] = 0;
            newAccelerations[j * dim + 1] = 0;
        }
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                if (j != k) {
                    double distance = bodies[j].calculateDistance(bodies[k]);
                    newAccelerations[j * dim] += G * bodies[k].getMass() / pow(distance, 2) * (positions[k * dim] - positions[j * dim]) / distance;
                    newAccelerations[j * dim + 1] += G * bodies[k].getMass() / pow(distance, 2) * (positions[k * dim + 1] - positions[j * dim + 1]) / distance;
                }
            }
        }
        // update the velocities
        for (size_t j = 0; j < n; j++) {
            velocities[j * dim] += 0.5 * (accelerations[j * dim] + newAccelerations[j * dim]) * timeStep;
            velocities[j * dim + 1] += 0.5 * (accelerations[j * dim + 1] + newAccelerations[j * dim + 1]) * timeStep;
        }
        // update the accelerations
        for (size_t j = 0; j < n; j++) {
            accelerations[j * dim] = newAccelerations[j * dim];
            accelerations[j * dim + 1] = newAccelerations[j * dim + 1];
        }
        // update the trajectory
        for (size_t j = 0; j < n; j++) {
            trajectory[i + 1][j * dim] = positions[j * dim];
            trajectory[i + 1][j * dim + 1] = positions[j * dim + 1];
        }
        
    }
    std::cout << "Updated trajectory\n";

    // update the bodies
    for (size_t i = 0; i < n; i++) {
        bodies[i].setX(positions[i * dim]);
        bodies[i].setY(positions[i * dim + 1]);
        bodies[i].setX_vel(velocities[i * dim]);
        bodies[i].setY_vel(velocities[i * dim + 1]);
    }
    std::cout << "Updated bodies\n";

    return trajectory;
}

#endif