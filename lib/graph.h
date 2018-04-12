#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <list>
#include <map>

struct Vertex;
using Edge = std::pair<std::shared_ptr<Vertex>, int>;
using VertexPtr = std::shared_ptr<Vertex>;

struct Vertex {
    std::string name;
    std::vector<Edge> neighbours;
    double longitude;
    double latitude;

    Vertex() = default;

    explicit Vertex(std::string _name, double _longitude,
                    double _latitude) : name(_name), longitude(_longitude),
                                        latitude(_latitude) {}

    bool operator<(const Vertex &other) const {
        return name < other.name;
    }
};


class Graph {
    std::map<std::string, VertexPtr> vertices;
public:
    void add_vertex(std::string name, double longitude, double latitude);

    void add_edge(const std::string &first,
                  const std::string &second, int weight);

    void print_graph() const noexcept;

    void BFS(const std::string &name, const std::string &name_dest) const;

    void DFS(const std::string &name, const std::string &name_dest) const;

    std::list<Vertex> trace_path(std::map<Vertex, Vertex> parent_map,
                                 Vertex start, Vertex dest) const;
};
