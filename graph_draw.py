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


def get_path(path_filename):
    longitudes = []
    latitudes = []
    with open(path_filename, 'r') as path_file:
        reader = csv.DictReader(path_file, fieldnames=['longitude', 'latitude'])
        for row in reader:
            longitudes.append(float(row['longitude']))
            latitudes.append(float(row['latitude']))
    return longitudes, latitudes


if __name__ == '__main__':
    csv_files = os.listdir('data/csv')
    for file in csv_files:
        longitudes, latitudes = get_tram_line(f'data/csv/{file}')
        plt.plot(longitudes, latitudes, marker='o', color='#1f77b4',
                 linestyle='-')
    longitudes, latitudes = get_path('path.dat')
    plt.plot(longitudes, latitudes, marker='o', color='#d62728',
             linestyle='-')
    plt.show()
