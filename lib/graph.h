#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include "vertex.h"
#include "path.h"

using VertexPtr = std::shared_ptr<Vertex>;


class Graph {
    std::map<std::string, VertexPtr> vertices;
public:
    void add_vertex(std::string name, double longitude, double latitude);

    void add_tramline_to_vertex(std::string vertex, std::string line);

    void add_edge(const std::string &first,
                  const std::string &second, int weight);

    void print_graph() const noexcept;

    Path BFS(const std::string &name, const std::string &name_dest) const;

    Path DFS(const std::string &name, const std::string &name_dest) const;

    Path a_star(const std::string &start, const std::string &dest) const;

    Path trace_path(std::map<Vertex, Vertex> parent_map,
                    Vertex start, Vertex dest) const;

    int get_heuristic_distance(const Vertex& from, const Vertex& to) const;

    int get_total_distance(const Vertex& from, const Vertex& to, int dist_done) const;

    int find_edge_weight(const Vertex& from, const Vertex& to) const;
};
