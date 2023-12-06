import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os
import glob

# Function to read all CSV files in a directory and return their coordinates
def read_coordinates(directory):
    # Get a list of all CSV files in the directory
    files = glob.glob(os.path.join(directory, '*.csv'))
    # Read each file and store its coordinates
    coordinates = [read_file(file) for file in files]
    return coordinates

# Function to read a single CSV file and return its coordinates
def read_file(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        # Skip the header if present
        header = next(reader)
        # Convert each row to a list of floats and store all rows
        coordinates = [list(map(float, row)) for row in reader]
    return coordinates

# Function to update the plot for each frame in the animation
def update(frame, *args):
    # Separate the planets and their data
    planets = args[::2]
    data = args[1::2]
    # Update each planet's position and size
    for planet, coordinates in zip(planets, data):
        planet.set_data(coordinates[frame][0], coordinates[frame][1])
        planet.set_markersize(2 * coordinates[frame][2])
    return planets

def main():
    # Set the working directory
    os.chdir('/Users/patrykkwoczak/Graduate School/AMS562/project/')
    directory = 'coords'

    # Read all coordinates from the CSV files in the directory
    coordinates = read_coordinates(directory)

    # Create a new plot
    fig, ax = plt.subplots()
    # Set the plot limits to the minimum and maximum coordinates
    min_x = min(c[0] for coords in coordinates for c in coords)
    max_x = max(c[0] for coords in coordinates for c in coords)
    min_y = min(c[1] for coords in coordinates for c in coords)
    max_y = max(c[1] for coords in coordinates for c in coords)
    
    ax.set_xlim(min_x, max_x)
    ax.set_ylim(min_y, max_y)

    # Create a plot object for each set of coordinates
    planets = [ax.plot([], [], 'o', markersize=2 * coords[0][2])[0] for coords in coordinates]

    # Create an animation with the update function and the coordinates
    ani = animation.FuncAnimation(fig, update, frames=min(len(coords) for coords in coordinates),
                                  fargs=tuple(sum(zip(planets, coordinates), ())),
                                  interval=50, blit=True)

    # Save the animation as a GIF
    ani.save('trajectory_animation.gif', writer='imagemagick')

    # Display the plot
    plt.show()

if __name__ == "__main__":
    main()