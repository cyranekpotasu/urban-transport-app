#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lib/graph.h"

std::string build_line_string(std::string line_filename) {
    auto stripped = line_filename.substr(11, 2);
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
    getline(record, latitude);
    graph.add_vertex(name, atof(longitude.c_str()),
                     atof(latitude.c_str()));

    while (getline(csv_file, line)) {
        std::istringstream record(line);
        std::string prev_name(name);
        getline(record, name, ',');
        getline(record, distance, ',');
        getline(record, longitude, ',');
        getline(record, latitude);
        graph.add_vertex(name, atof(longitude.c_str()),
                         atof(latitude.c_str()));
        graph.add_tramline_to_vertex(name, tram_line);
        graph.add_edge(prev_name, name, atoi(distance.c_str()));
    }

}

void load_graph(Graph& graph) {
    std::vector<std::string> csv_files{};
    std::ifstream csv_stream("csv_files.txt");
    while (!csv_stream.eof()) {
        std::string file;
        csv_stream >> file;
        if(!file.empty())
            csv_files.push_back(file);
    }
    for (auto &&file: csv_files) {
        load_tram_line(graph, "data/csv/" + file);
    }
}

int main(int argc, char** argv) {
    Graph g;
    load_graph(g);
    int choice, alg_choice;
    Path path;
    std::string starting, final, filename;
    if(argc == 1) {
        return 0;
    }
    starting = argv[1];
    final = argv[2];
    if(std::string("dfs") == argv[3])
        path = g.DFS(starting, final);
    else if(std::string("bfs") == argv[3])
        path = g.BFS(starting, final);
    else
        path = g.a_star(starting, final);
    path.print_path();
    path.export_path("path.dat");
}












