#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <list>
#include <map>


struct Vertex {
    using Edge = std::pair<std::shared_ptr<Vertex>, int>;
    std::string name;
    std::vector<Edge> neighbours;

    explicit Vertex(std::string _name) : name(_name) {}
};

using VertexPtr = std::shared_ptr<Vertex>;

class Graph {
    std::map<std::string, VertexPtr> vertices;
public:
    void add_vertex(std::string name);

    void add_edge(const std::string &first,
                  const std::string &second, int weight);

    void print_graph() const noexcept;

    void BFS(const std::string &name, const std::string &name_dest) const;

    void DFS(const std::string &name, const std::string &name_dest) const;

    std::list<Vertex> trace_path(const std::map<Vertex, Vertex> &parent_map,
                                 const Vertex &start, const Vertex &dest) const;
};
