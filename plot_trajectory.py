
import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

def read_coordinates(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        header = next(reader)  # Skip the header if present
        coordinates = [list(map(float, row)) for row in reader]
    return coordinates

def update(frame, data1, planet1, data2, planet2):
    planet1.set_data(data1[frame][0], data1[frame][1])
    planet2.set_data(data2[frame][0], data2[frame][1])
    return planet1, planet2,

def main():
    os.chdir('/Users/patrykkwoczak/Graduate School/AMS562/project/')
    filename1 = 'coords/body1_coordinates.csv'
    filename2 = 'coords/body2_coordinates.csv'

    coordinates1 = read_coordinates(filename1)
    coordinates2 = read_coordinates(filename2)

    fig, ax = plt.subplots()
    min_x = min(min(c[0] for c in coordinates1), min(c[0] for c in coordinates2))
    max_x = max(max(c[0] for c in coordinates1), max(c[0] for c in coordinates2))
    min_y = min(min(c[1] for c in coordinates1), min(c[1] for c in coordinates2))
    max_y = max(max(c[1] for c in coordinates1), max(c[1] for c in coordinates2))
    
    ax.set_xlim(min_x, max_x)
    ax.set_ylim(min_y, max_y)

    radius1 = coordinates1[0][2]
    radius2 = coordinates2[0][2]

    planet1, = ax.plot([], [], 'bo', markersize=2 * radius1)
    planet2, = ax.plot([], [], 'ro', markersize=2 * radius2)

    ani = animation.FuncAnimation(fig, update, frames=min(len(coordinates1), len(coordinates2)),
                                  fargs=(coordinates1, planet1, coordinates2, planet2),
                                  interval=50, blit=True)

    ani.save('trajectory_animation.gif', writer='imagemagick')

    plt.show()

if __name__ == "__main__":
    main()