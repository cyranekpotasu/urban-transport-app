//
// Created by cyran on 08.04.18.
//
#include "../lib/graph.h"

void Graph::add_vertex(std::string name, double longitude, double latitude) {
    if (vertices.find(name) == vertices.end()) {
        auto v = std::make_shared<Vertex>(name, longitude, latitude);
        vertices[name] = v;
    }
}

void Graph::add_edge(const std::string &first,
                     const std::string &second, int weight) {
    if (first == second)
        return;
    auto first_vertex = vertices[first];
    auto second_vertex = vertices[second];
    for (const auto &neighbour: first_vertex->neighbours) {
        if (neighbour.first->name == second)
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

void Graph::BFS(const std::string &name, const std::string &name_dest) const {
    /* Map to check wheter vertex was visited */
    std::map<std::string, bool> visited;
    std::map<Vertex, Vertex> parent_map;
    /* Fill visited with false */
    for (const auto &vertex : vertices)
        visited[vertex.first] = false;
    /* Mark first visited as true */
    visited[name] = true;
    /* Create a queue for BFS */
    std::list<VertexPtr> queue;
    queue.push_back(this->vertices.at(name));
    while (!queue.empty()) {
        auto x = queue.front();
        queue.pop_front();
        if (x->name == name_dest) {
            trace_path(parent_map, *vertices.at(name), *vertices.at(name_dest));
            return;
        }
        for (const auto &neighbour : x->neighbours) {
            if (!visited.at(neighbour.first->name)) {
                parent_map[*neighbour.first] = *x;
                visited[neighbour.first->name] = true;
                queue.push_back(neighbour.first);
            }
        }
    }
}

void Graph::DFS(const std::string &name, const std::string &name_dest) const {
    /* Map to check wheter vertex was visited */
    std::map<std::string, bool> visited;
    std::map<Vertex, Vertex> parent_map;
    /* Fill visited with false */
    for (const auto &vertex : vertices)
        visited[vertex.first] = false;
    /* Mark first visited as true */
    visited[name] = true;
    /* Create a queue for BFS */
    std::list<VertexPtr> stack;
    stack.push_back(this->vertices.at(name));
    while (!stack.empty()) {
        auto x = stack.back();
        stack.pop_back();
        if (x->name == name_dest) {
            trace_path(parent_map, *vertices.at(name), *vertices.at(name_dest));
            return;
        }
        for (const auto &neighbour : x->neighbours) {
            if (!visited.at(neighbour.first->name)) {
                parent_map[*neighbour.first] = *x;
                visited[neighbour.first->name] = true;
                stack.push_back(neighbour.first);
            }
        }
    }
}

std::list<Vertex> Graph::trace_path(std::map<Vertex, Vertex> parent_map,
                                    Vertex start, Vertex end) const {
    int weight = 0;
    std::list<Vertex> path;
    path.push_front(end);
    while (end.name != start.name) {
        auto prev = end;
        end = parent_map[end];
        weight += find_edge_weight(prev, end);
        path.push_front(end);
    }
    for (const auto &node: path)
        std::cout << node.name << " -> ";
    std::cout << std::endl << "Path length: " << weight << std::endl;
    return path;
}

int Graph::get_heuristic_distance(const Vertex &from, const Vertex &to) const {
    auto lon_distance = (from.longitude - to.longitude) * 300;
    auto lat_distance = (from.latitude - to.latitude) * 300;
    return static_cast<int>(sqrt(lon_distance * lon_distance + lat_distance * lat_distance));
}

int Graph::get_total_distance(const Vertex &from, const Vertex &to, int dist_done) const {
    return get_heuristic_distance(from, to) + dist_done;
}

void Graph::a_star(const std::string &start, const std::string &dest) const {
    struct Node {
        int distance;
        int distance_from_start;
        VertexPtr path_extension;

        Node() = default;
        Node(VertexPtr vertex, int dist, int total_dist) : path_extension(vertex),
                                                           distance_from_start(dist),
                                                           distance(total_dist) {}

        bool operator<(const Node &rhs) const { return this->distance > rhs.distance; }
    };

    std::priority_queue<Node> open;
    std::set<VertexPtr> closed;
    std::map<std::string, Node> visited;
    std::map<Vertex, Vertex> parent_map;
    auto destination = vertices.at(dest);
    open.emplace(Node(vertices.at(start), 0, 0));
    while (open.top().path_extension->name != dest) {
        auto current = open.top();
        open.pop();
        closed.insert(current.path_extension);
        for (const auto &neighbour: current.path_extension->neighbours) {
            auto neighbour_vertex = neighbour.first;
            if (closed.find(neighbour_vertex) == closed.end()) {
                int dist_from_start = current.distance_from_start + neighbour.second;
                int total_dist = get_total_distance(*neighbour_vertex, *destination,
                                                    dist_from_start);
                auto next = Node(neighbour_vertex, dist_from_start, total_dist);
                auto visited_node = visited.find(neighbour_vertex->name);
                if (visited_node == visited.end() ||
                    (*visited_node).second.distance > next.distance) {
                    open.push(next);
                    visited[neighbour_vertex->name] = next;
                    parent_map[*neighbour_vertex] = *current.path_extension;
                }
            }
        }
    }
    trace_path(parent_map, *vertices.at(start), *vertices.at(dest));
}

int Graph::find_edge_weight(const Vertex &from, const Vertex &to) const {
    for (const auto &neighbour: from.neighbours) {
        if (neighbour.first->name == to.name)
            return neighbour.second;
    }
}

