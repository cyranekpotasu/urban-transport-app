#!/usr/bin/python3

import csv
import os
import sys
import subprocess

from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QComboBox, QMessageBox, QLabel, QGridLayout, \
    QRadioButton, QButtonGroup
from PyQt5.QtGui import QPixmap


def get_stop_names():
    stops = set()
    filenames = os.listdir('data/csv')
    for filename in filenames:
        with open('data/csv/' + filename, 'r') as file:
            reader = csv.DictReader(file)
            for row in reader:
                stops.add(row['name'])
    return sorted(list(stops))


class App(QWidget):
    def __init__(self):
        super().__init__()
        self.algorithm_dict = {'DFS': 'dfs', 'BFS': 'bfs',
                               'A*': 'astar'}
        self.alg_option = 'dfs'
        self.title = 'PyQt demo'
        self.initUI()

    def initUI(self):
        start = QLabel('Start: ', self)
        dest = QLabel('Destination: ', self)
        self.city_map = QLabel(self)
        algorithm_label = QLabel('Algorithm: ', self)
        self.pixmap = QPixmap('map.png').scaledToWidth(500)
        self.city_map.setPixmap(self.pixmap)
        find = QPushButton('Find path', self)
        find.clicked.connect(self.find_path)
        self.path_label = QLabel('', self)

        tram_stops = get_stop_names()

        self.combo_start = QComboBox(self)
        self.combo_start.addItems(tram_stops)
        self.combo_start.setMaxVisibleItems(15)

        self.combo_dest = QComboBox(self)
        self.combo_dest.addItems(tram_stops)
        self.combo_start.setMaxVisibleItems(15)

        algorithms = [QRadioButton('DFS'), QRadioButton('BFS'),
                      QRadioButton('A*')]

        grid = QGridLayout()
        grid.setSpacing(10)

        grid.addWidget(start, 1, 0)
        grid.addWidget(self.combo_start, 1, 1, 1, 5)

        grid.addWidget(dest, 2, 0)
        grid.addWidget(self.combo_dest, 2, 1, 1, 5)

        grid.addWidget(self.city_map, 4, 0, 1, 6)

        grid.addWidget(self.path_label, 5, 0, 5, 5)
        grid.addWidget(find, 5, 5)

        self.buttons = QButtonGroup()
        grid.addWidget(algorithm_label, 3, 0)
        for i, radio in enumerate(algorithms):
            grid.addWidget(radio, 3, i + 1)
            self.buttons.addButton(radio, i)
            radio.toggled.connect(self.set_algorithm)

        self.setLayout(grid)

        self.setWindowTitle(self.title)
        self.show()

    def set_algorithm(self):
        self.alg_option = self.algorithm_dict[
            self.buttons.checkedButton().text()]

    def find_path(self):
        path = subprocess.check_output(['./cmake-build-debug/UrbanTransportApp',
                                        self.combo_start.currentText(),
                                        self.combo_dest.currentText(),
                                        self.alg_option]).decode('utf-8')
        self.path_label.setText(path)
        subprocess.run(['./graph_draw.py', 'path.dat'])
        self.city_map.setPixmap(QPixmap('path.png').scaledToWidth(500))



if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
