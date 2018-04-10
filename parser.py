import xml.etree.ElementTree as ET
import csv

import os


def get_coordinates_data():
    coord_data = {}
    with open('data/coordinates.csv', 'r') as csvfile:
        reader = csv.DictReader(csvfile, delimiter=';')
        for row in reader:
            coord_data[row['ID']] = (row['longitude'], row['latitude'])
    return coord_data


def make_csv(line):
    tree = ET.parse(f'data/xml/{line}.xml')
    root = tree.getroot()

    main_variant = root.find('.//wariant[@id="1"]')
    with open(f'data/csv/{line}.csv', 'w') as csvfile:
        field_names = ['name',
                       'distance', 'longitude', 'latitude']
        writer = csv.DictWriter(csvfile, field_names)
        writer.writeheader()
        for stop in main_variant.iter('przystanek'):
            stop_id = stop.get('id')
            name = stop.get('nazwa')
            table = stop.find('tabliczka')
            mc = table.get('mc') if table else '0'
            writer.writerow({'name': name,
                             'distance': mc,
                             'longitude': coordinates[stop_id][0],
                             'latitude': coordinates[stop_id][1]})


coordinates = get_coordinates_data()

if __name__ == '__main__':
    file_names = [file.split('.')[0] for file in os.listdir('data/xml')]
    for file_name in file_names:
        make_csv(file_name)
