//
// Created by cyran on 08.04.18.
//

#include <iomanip>
#include "../lib/graph.h"

void Graph::add_vertex(std::string name) {
    if (vertices.find(name) == vertices.end()) {
        auto v = std::make_shared<Vertex>(name);
        vertices[name] = v;
    }
}

void Graph::add_edge(const std::string &first,
                     const std::string &second, int weight) {
    if(first == second)
        return;
    auto first_vertex = vertices[first];
    auto second_vertex = vertices[second];
    for(const auto& neighbour: first_vertex->neighbours){
            if(neighbour.first->name == second)
                return;
    }
        first_vertex->neighbours.emplace_back(
                std::make_pair(second_vertex, weight)
        );

        second_vertex->neighbours.emplace_back(
                std::make_pair(first_vertex, weight)
        );
}

void Graph::print_graph() const noexcept {
    for (const auto &vertex: vertices) {
        std::cout << vertex.first << " neighbours: " << std::endl;
        for (const auto &neighbour: vertex.second->neighbours)
            std::cout << "\t" << neighbour.first->name << " distance: "
                      << neighbour.second;
        std::cout << std::endl;
    }
}
