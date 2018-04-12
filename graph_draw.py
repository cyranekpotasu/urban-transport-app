import matplotlib.pyplot as plt
import csv

import os


def get_tram_line(csv_filename):
    longitudes = []
    latitudes = []
    with open(csv_filename, 'r') as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            longitudes.append(float(row['longitude']))
            latitudes.append(float(row['latitude']))
    return longitudes, latitudes


if __name__ == '__main__':
    csv_files = os.listdir('data/csv')
    for file in csv_files:
        longitudes, latitudes = get_tram_line(f'data/csv/{file}')
        plt.plot(longitudes, latitudes, 'o-')
    plt.show()
