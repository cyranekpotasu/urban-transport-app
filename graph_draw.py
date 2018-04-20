#!/usr/bin/python3

import os
import csv
import argparse

import matplotlib.pyplot as plt


def get_tram_line(csv_filename):
    longitudes = []
    latitudes = []
    with open(csv_filename, 'r') as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            longitudes.append(float(row['longitude']))
            latitudes.append(float(row['latitude']))
    return longitudes, latitudes


def draw_city_graph():
    csv_files = os.listdir('data/csv')
    for file in csv_files:
        longitudes, latitudes = get_tram_line(f'data/csv/{file}')
        plt.plot(longitudes, latitudes, marker='o', color='#1f77b4',
                 linestyle='-')


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
    parser = argparse.ArgumentParser(description="Plot searched path from file")
    parser.add_argument('file', help='File with data to plot')
    args = parser.parse_args()

    fig = plt.figure(frameon=False)
    ax = plt.Axes(fig, [0., 0., 1., 1.])
    ax.set_axis_off()
    fig.add_axes(ax)
    draw_city_graph()

    longitudes, latitudes = get_path(args.file)
    plt.plot(longitudes, latitudes, marker='o', color='#d62728',
             linestyle='-')
    plt.savefig('path.png')
