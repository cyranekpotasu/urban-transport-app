#include<iostream>
#include <memory>
#include <vector>
#include <map>

struct Vertex {
    using Edge = std::pair<std::shared_ptr<Vertex>, int>;
    std::string name;
    std::vector<Edge> neighbours;

    explicit Vertex(std::string&& _name): name(std::move(_name)) {}
};

class Graph
{
    std::map<std::string, std::shared_ptr<Vertex>> vertices;
public:
    void add_vertex(std::string&& name);
    void add_edge(const std::string& first,
                  const std::string& second, int weight);
    void print_graph() const noexcept;
};
