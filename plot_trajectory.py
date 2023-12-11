
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

def update(frame, data1, body1, data2, body2):
    body1.set_data(data1[frame][0], data1[frame][1])
    body2.set_data(data2[frame][0], data2[frame][1])
    return body1, body2,

def main():
    os.chdir('/Users/giorgoskementzidis/Library/CloudStorage/OneDrive-Personal/repos/ams_562/Celestial_Bodies/')
    filename1 = 'coords/star1_coordinates.csv'
    filename2 = 'coords/planet1_coordinates.csv'

    coordinates1 = read_coordinates(filename1)
    coordinates2 = read_coordinates(filename2)

    fig, ax = plt.subplots()
    min_x = min(min(c[0] for c in coordinates1), min(c[0] for c in coordinates2))
    max_x = max(max(c[0] for c in coordinates1), max(c[0] for c in coordinates2))
    min_y = min(min(c[1] for c in coordinates1), min(c[1] for c in coordinates2))
    max_y = max(max(c[1] for c in coordinates1), max(c[1] for c in coordinates2))

    minimum = min(min_x, min_y)
    maximum = max(max_x, max_y)
    
    # ax.set_xlim(min_x, max_x)
    # ax.set_ylim(min_y, max_y)

    ax.set_xlim(minimum, maximum)
    ax.set_ylim(minimum, maximum)

    radius1 = coordinates1[0][2]
    radius2 = coordinates2[0][2]

    body1, = ax.plot([], [], 'bo', markersize=1 * radius1)
    body2, = ax.plot([], [], 'ro', markersize=1 * radius2)

    ani = animation.FuncAnimation(fig, update, frames=min(len(coordinates1), len(coordinates2)),
                                  fargs=(coordinates1, body1, coordinates2, body2),
                                  interval=50, blit=True)

    ani.save('trajectory_animation_TEST_01.gif', writer='imagemagick')

    plt.show()

if __name__ == "__main__":
    main()