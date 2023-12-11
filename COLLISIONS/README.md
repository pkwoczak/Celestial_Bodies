All files that are consistent with the feature allowing inelastic collisions.

You can run the simulateCollision.cpp to re-create a collision betweem a planet and an asteroid. 

You can change the setup of the bodies included within the main function.

So, first you run the cpp file:
g++ -std=c++11 -o test simulateCollision.cpp

You run the executable:
./test

And then, you run the plot_all_trajectories.py python script:
python3 plot_all_trajectories.py 

Within this python script, you can adjust the size of the objects included in the simulation by changing the scalar on line 33. 

You may also edit the name of the saved file, as well as the path of the directory where you want to save the generated gif file.

Make sure that you delete any files from the coords folder before re-running the program.
