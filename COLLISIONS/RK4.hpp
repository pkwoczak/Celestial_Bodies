#ifndef RK4_HPP
#define RK4_HPP
#include "body.hpp"
#include <cmath>
#include <vector>

#define G 1.0

// Fourth-order Runge-Kutta method
// Let ODE be x' = f(x, t), x(0) = x0
// Then x(t_n+1) = x(t_n) + (1/6)(k1 + 2k2 + 2k3 + k4)*h
// where h = t_n+1 - t_n
// k1 = f(x_n, t_n)
// k2 = f(x_n + (1/2)k1*h, t_n + (1/2)*h)
// k3 = f(x_n + (1/2)k2*h, t_n + (1/2)*h)
// k4 = f(x_n + k3*h, t_n + h)

// Let x be a vector of size 2*n*dim, where n is the number of bodies and dim is the dimension of the system
// x = [pos1, pos2, ..., posn, vel1, vel2, ..., veln]
// Let f(x, t) = [vel1, vel2, ..., veln, acc1, acc2, ..., accn]
// Then x' = f(x, t) = [vel1, vel2, ..., veln, acc1, acc2, ..., accn]

// store trajectory of a body during a time step by vector<vector<double>>

// write a function for f(x, t)
// return f with a vector of size 2*n*dim same as x
std::vector<double> one_iter(std::vector<double> &x, size_t n, size_t dim, std::vector<double> &masses){
    // x = [pos1, pos2, ..., posn, vel1, vel2, ..., veln]
    // f(x, t) = [vel1, vel2, ..., veln, acc1, acc2, ..., accn]
    // initialize f with zeros
    std::vector<double> f(2*n*dim, 0);
    // first n*dim elements are velocities
    for (size_t i = 0; i < n*dim; i++){
        f[i] = x[i + n*dim];
    }
    // last n*dim elements are accelerations
    // compute accelerations between each pair of bodies
    for (size_t i = 0; i < n; i++){
        for (size_t j = i+1; j < n; j++){
            // compute distance between body i and body j
            double dist = 0;
            for (size_t k = 0; k < dim; k++){
                dist += pow(x[i*dim + k] - x[j*dim + k], 2);
            }
            dist = sqrt(dist);
            // compute acceleration of body i and body j
            double acc = G/(dist*dist*dist);
            // update acceleration of body i 
            for (size_t k = 0; k < dim; k++){
                f[i*dim + n*dim + k] += acc*masses[j]*x[j*dim + k];
            }
            // update acceleration of body j
            for (size_t k = 0; k < dim; k++){
                f[j*dim + n*dim + k] -= acc*masses[i]*x[i*dim + k];
            }
        }
    }
    return f;
}


std::vector<std::vector<double>> RK4(std::vector<Body> &bodies, double timeStep, double endTime){
    // number of bodies
    size_t n = bodies.size();
    // dimension of the system
    size_t dim = 2;
    // number of time steps
    size_t numSteps = endTime/timeStep;
    // store trajectory of each body with n*dim columns and numSteps+1 rows
    std::vector<std::vector<double>> trajectory(numSteps+1, std::vector<double>(n*dim, 0));
    // initialize trajectory size 2*n*dim
    // first n*dim elements are positions
    // last n*dim elements are velocities
    for (size_t i = 0; i < n; i++){
        trajectory[0][i*dim] = bodies[i].getX();
        trajectory[0][i*dim + 1] = bodies[i].getY();
        trajectory[0][i*dim + n*dim] = bodies[i].getX_vel();
        trajectory[0][i*dim + n*dim + 1] = bodies[i].getY_vel();
    }
    // initialize masses
    std::vector<double> masses(n, 0);
    for (size_t i = 0; i < n; i++){
        masses[i] = bodies[i].getMass();
    }
    // iterate over time steps
    // use one_iter to compute f(x, t)
    // update x(t_n+1) = x(t_n) + (1/6)(k1 + 2k2 + 2k3 + k4)*h
    for (size_t i = 0; i < numSteps; i++){
        // compute k1
        std::vector<double> k1 = one_iter(trajectory[i], n, dim, masses);
        // compute k2
        std::vector<double> k2(2*n*dim, 0);
        for (size_t j = 0; j < 2*n*dim; j++){
            k2[j] = trajectory[i][j] + 0.5*timeStep*k1[j];
        }
        k2 = one_iter(k2, n, dim, masses);
        // compute k3
        std::vector<double> k3(2*n*dim, 0);
        for (size_t j = 0; j < 2*n*dim; j++){
            k3[j] = trajectory[i][j] + 0.5*timeStep*k2[j];
        }
        k3 = one_iter(k3, n, dim, masses);
        // compute k4
        std::vector<double> k4(2*n*dim, 0);
        for (size_t j = 0; j < 2*n*dim; j++){
            k4[j] = trajectory[i][j] + timeStep*k3[j];
        }
        k4 = one_iter(k4, n, dim, masses);
        // update trajectory
        for (size_t j = 0; j < 2*n*dim; j++){
            trajectory[i+1][j] = trajectory[i][j] + (1.0/6.0)*(k1[j] + 2*k2[j] + 2*k3[j] + k4[j])*timeStep;
        }
    }
    // update bodies
    // set X and X_vel of each body
    // also set Y and Y_vel of each body
    for (size_t i = 0; i < n; i++){
        bodies[i].setX(trajectory[numSteps][i*dim]);
        bodies[i].setY(trajectory[numSteps][i*dim + 1]);
        bodies[i].setX_vel(trajectory[numSteps][i*dim + n*dim]);
        bodies[i].setY_vel(trajectory[numSteps][i*dim + n*dim + 1]);
    }
    return trajectory;
}



#endif
