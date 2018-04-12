#include <iostream>
#include <fstream>
#include <sstream>
#include "lib/graph.h"

void load_tram_line(Graph &graph, std::string csv_filename) {
    std::ifstream csv_file(csv_filename);
    std::string line;
    getline(csv_file, line);
    getline(csv_file, line);
    std::istringstream record(line);
    std::string name, distance, longitude, latitude;
    getline(record, name, ',');
    getline(record, distance, ',');
    getline(record, longitude, ',');
    record >> latitude;
    graph.add_vertex(name, atof(longitude.c_str()),
                     atof(latitude.c_str()));

    while (getline(csv_file, line)) {
        std::istringstream record(line);
        std::string prev_name(name);
        getline(record, name, ',');
        graph.add_vertex(name, atof(longitude.c_str()),
                         atof(latitude.c_str()));
        graph.add_edge(prev_name, name, atoi(distance.c_str()));
        getline(record, distance, ',');
        getline(record, longitude, ',');
        record >> latitude;
    }

}

int main() {
    Graph g;
    std::vector<std::string> csv_files{};
    std::ifstream csv_stream("../csv_files.txt");
    while (!csv_stream.eof()) {
        std::string file;
        csv_stream >> file;
        csv_files.push_back(file);
    }
    for (auto &&file: csv_files) {
        load_tram_line(g, "../data/csv/" + file);
    }
    g.print_graph();
    std::cout << std::endl;
    g.BFS("ZOO", "Prusa");
    g.BFS("KLECINA", "Dmowskiego");
    g.a_star("KLECINA", "Dmowskiego");
}

