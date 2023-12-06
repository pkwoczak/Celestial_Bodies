#ifndef SAVE_TRAJECTORIES_HPP
#define SAVE_TRAJECTORIES_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "save_coords.hpp"

void saveTrajectories(const std::vector<std::vector<std::vector<double> > >& Trajectories);

//Trajectory is in vector<vector<vector>> format
// inside vector<vector> is position of all bodies at one time step
// inside vector is position of one body and its radius (x, y, radius)
// outer vector is time
// the size is (n_timesteps+1)nbodies3
void saveTrajectories(const std::vector<std::vector<std::vector<double> > >& Trajectories) {

    //Determine number of bodies by checking size
    if (Trajectories.empty() || Trajectories[0].empty()) {
        std::cerr << "Error: Trajectories is empty" << std::endl;
        return;
    }
    int nBodies = Trajectories[0].size();


    for(int body_i = 0; body_i < nBodies; body_i++){
        std::vector<std::vector<double> > singleBodyTrajectory;

        //fill in singleBodyTrajectory with positions and radius for one body accross
        //all time steps
        for(const auto& timestep : Trajectories) {
            if(body_i < timestep.size()) {
                singleBodyTrajectory.push_back(timestep[body_i]);
            }
        }

        //save singleBodyTrajectory to file
        std::ostringstream filenameStream;
        filenameStream << "coords/body_" << body_i+1 << "_trajectory.csv";
        std::string filename = filenameStream.str();

        //use saveCoords to save singleBodyTrajectory
        saveCoordinates(singleBodyTrajectory, filename);
    }

}

#endif // SAVE_TRAJECTORIES_HPP
