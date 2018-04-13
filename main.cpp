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
    getline(record, latitude);
//    std::cout << name << " "<< longitude << " " << latitude << std::endl;
    graph.add_vertex(name, atof(longitude.c_str()),
                     atof(latitude.c_str()));

    while (getline(csv_file, line)) {
        std::istringstream record(line);
        std::string prev_name(name);
        getline(record, name, ',');
        getline(record, distance, ',');
        getline(record, longitude, ',');
        getline(record, latitude);
//        std::cout << name << " " << longitude << " " << latitude << std::endl;
        graph.add_vertex(name, atof(longitude.c_str()),
                         atof(latitude.c_str()));
        graph.add_tramline_to_vertex(name, tram_line);
        graph.add_edge(prev_name, name, atoi(distance.c_str()));
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

int show_menu() {
    std::cout << "Choose option:" << std::endl;
    std::cout << "\t1 - show all tram stops" << std::endl;
    std::cout << "\t2 - search shortest path" << std::endl;
    std::cout << "\t3 - exit" << std::endl;
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;
    return choice;
}

int find_path_menu() {
    std::cout << "Choose path searching algorithm: " << std::endl;
    std::cout << "\t1 - DFS - depth first search" << std::endl;
    std::cout << "\t2 - BFS - breadth first search" << std::endl;
    std::cout << "\t3 - A*" << std::endl;
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;
    return choice;
}

int main() {
    Graph g;
    load_graph(g);
    int choice, alg_choice;
    Path path;
    std::string starting, final;
    while(true) {
        int choice = show_menu();
        switch(choice) {
            case 1:
                g.print_graph(false);
                break;

            case 2:
            std::cin.ignore();
            std::cout << "Choose starting station: ";
            getline(std::cin, starting);
            std::cout << "Choose final station: ";
            getline(std::cin, final);
                alg_choice = find_path_menu();
                switch(alg_choice) {
                    case 1:
                        path = g.DFS(starting, final);
                        path.print_path();
                        break;
                    case 2:
                        path = g.BFS(starting, final);
                        path.print_path();
                        break;
                    case 3:
                        path = g.a_star(starting, final);
                        path.print_path();
                        break;
                    default:
                    std::cout << "Wrong option. Returning to main menu.";
                }
                break;

            case 3:
                return 0;

            default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }

    }
}












