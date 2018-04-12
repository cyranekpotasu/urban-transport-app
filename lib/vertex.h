#ifndef URBANTRANSPORTAPP_VERTEX_H
#define URBANTRANSPORTAPP_VERTEX_H

#include <vector>
#include <memory>
#include <set>

struct Vertex {
    using Edge = std::pair<std::shared_ptr<Vertex>, int>;
    std::string name;
    std::vector<Edge> neighbours;
    std::set<std::string> tram_lines = {};
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

#endif //URBANTRANSPORTAPP_VERTEX_H
