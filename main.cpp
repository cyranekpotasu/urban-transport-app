#include <iostream>
#include <fstream>
#include <sstream>
#include "lib/graph.h"

std::string build_line_string(std::string line_filename) {
    auto stripped = line_filename.substr(14, 2);
    if (stripped[0] == '0' && isdigit(stripped[1]))
        return stripped.substr(1, 1);
    else return stripped.substr(0, 2);


}

void load_tram_line(Graph &graph, std::string csv_filename) {
    std::ifstream csv_file(csv_filename);
    std::string line;
    auto tram_line = build_line_string(csv_filename);
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
        graph.add_tramline_to_vertex(name, tram_line);
        graph.add_edge(prev_name, name, atoi(distance.c_str()));
        getline(record, distance, ',');
        getline(record, longitude, ',');
        record >> latitude;
    }

}

void load_graph(Graph& graph) {
    std::vector<std::string> csv_files{};
    std::ifstream csv_stream("../csv_files.txt");
    while (!csv_stream.eof()) {
        std::string file;
        csv_stream >> file;
        if(!file.empty())
            csv_files.push_back(file);
    }
    for (auto &&file: csv_files) {
        load_tram_line(graph, "../data/csv/" + file);
    }
}

int main() {
    Graph g;
    load_graph(g);
    auto bfs_path = g.BFS("GAJ", "LEŚNICA");
    auto astar_path = g.a_star("GAJ", "LEŚNICA");
    bfs_path.print_path();
    astar_path.print_path();
}












