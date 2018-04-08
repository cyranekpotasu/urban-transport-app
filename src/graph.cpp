//
// Created by cyran on 08.04.18.
//

#include <iomanip>
#include "../lib/graph.h"

void Graph::add_vertex(std::string &&name) {
    auto v = std::make_shared<Vertex>(std::move(name));
    vertices[name] = v;
}

void Graph::add_edge(const std::string &first,
                     const std::string &second, int weight) {
    auto first_vertex = vertices[first];
    auto second_vertex = vertices[second];

    first_vertex->neighbours.emplace_back(
            std::make_pair(second_vertex, weight)
    );

    second_vertex->neighbours.emplace_back(
            std::make_pair(first_vertex, weight)
    );
}

void Graph::print_graph() const noexcept {
    for(const auto& vertex: vertices) {
        std::cout << vertex.first << 'neighbours: ' << std::endl;
        for(const auto& neighbour: vertex.second->neighbours)
            std::cout << std::setw(4)
                      << neighbour.first->name << "weight: "
                      << neighbour.second;
    }
}
