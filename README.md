# Celestial_Bodies
Simulation of N Celestial Bodies Interacting under a gravitational potential.

You can run the scripts simulateOrbit.cpp, simulateElliptic.cpp, simulateStars.cpp, simulateAsteroid.cpp to re-create the gif's from our presentation. You can also change the system content by editing the body definitions in the main() function.

So, first you run the cpp file:
g++ -std=c++11 -o test simulateOrbit.cpp

You run the executable:
./test

And then, you run the plot_all_trajectories.py python script:
python3 plot_trajectory.py 

Within this python script, you can adjust the size of the objects included in the simulation by changing the scalar on lines 45-46.
