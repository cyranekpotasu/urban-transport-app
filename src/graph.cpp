//
// Created by cyran on 08.04.18.
//
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

void Graph::BFS(const std::string& name, const std::string& name_dest) const {
	/* Map to check wheter vertex was visited */
	std::map<std::string, bool> visited;
	/* Fill visited with false */
	for(const auto& vertex : vertices)
		visited[vertex.first] = false;
	/* Mark first visited as true */
	visited[name] = true;
	/* Create a queue for BFS */
	std::list<VertexPtr> queue;
	queue.push_back(this->vertices.at(name));
	while(!queue.empty()){
		auto x = queue.front();
		std::cout << x->name << ",";
		queue.pop_front();
		if(x->name == name_dest)
			return;
		for(const auto& neighbour : x->neighbours){
			if(!visited.at(neighbour.first->name)){
				visited[neighbour.first->name] = true;
				queue.push_back(neighbour.first);
			}
		}
	}
}

void Graph::DFS(const std::string& name, const std::string& name_dest) const{
    /* Map to check wheter vertex was visited */
    std::map<std::string, bool> visited;
    /* Fill visited with false */
    for(const auto& vertex : vertices)
        visited[vertex.first] = false;
    /* Mark first visited as true */
    visited[name] = true;
    /* Create a queue for BFS */
    std::list<VertexPtr> stack;
    stack.push_back(this->vertices.at(name));
    while(!stack.empty()){
        auto x = stack.back();
        std::cout << x->name << ",";
        stack.pop_back();
        if(x->name == name_dest)
            return;
        for(const auto& neighbour : x->neighbours){
            if(!visited.at(neighbour.first->name)){
                visited[neighbour.first->name] = true;
                stack.push_back(neighbour.first);
            }
        }
    }
}

std::list<Vertex> Graph::trace_path(const std::map<Vertex, Vertex>& parent_map,
                                           const Vertex &start, const Vertex &end) const {
    std::list<Vertex> path;
	auto current = end;
    path.push_front(current);
    while(current.name != start.name) {
//        current = parent_map[current];
        path.push_front(current);
    }
    for(const auto& node: path)
        std::cout << node.name << " -> ";
    std::cout << std::endl;
    return path;
}
