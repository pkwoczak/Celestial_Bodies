#ifndef INTERACTIONS_HPP
#define INTERACTIONS_HPP

#include <iostream>
#include <vector>
#include "planet.hpp"
#include "body.hpp"

// set the acceleartion of each body to 0
// to be used at the beginning of each time step
void resetAcceleration(std::vector<Body*>& system){
    for (int i = 0; i < system.size(); i++){
        system[i]->setX_acc(0);
        system[i]->setY_acc(0);
    }
} 

#endif