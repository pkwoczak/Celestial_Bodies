import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

def read_coordinates(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        header = next(reader)  # Skip the header
        coordinates = [list(map(float, row)) for row in reader]
    return coordinates

def update(frame, data, planet):
    planet.set_data(data[frame][0], data[frame][1])
    return planet,

def main():
    #os.chdir('/Users/patrykkwoczak/Graduate School/AMS562/project/')
    filename = 'coords/planet1_coordinates.csv'
    coordinates = read_coordinates(filename)

    fig, ax = plt.subplots()
    ax.set_xlim(min(c[0] for c in coordinates), max(c[0] for c in coordinates))
    ax.set_ylim(min(c[1] for c in coordinates), max(c[1] for c in coordinates))

    # Assuming the radius is constant for all points in the trajectory
    radius = coordinates[0][2]
    
    planet, = ax.plot([], [], 'bo', markersize=2 * radius)

    ani = animation.FuncAnimation(fig, update, frames=len(coordinates), fargs=(coordinates, planet),
                                  interval=50, blit=True)

    ani.save('trajectory_animation.gif', writer='imagemagick')

    plt.show()

if __name__ == "__main__":
    main()