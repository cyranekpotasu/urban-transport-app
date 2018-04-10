#include <iostream>
#include "lib/graph.h"

int main() {
    Graph g;
    g.add_vertex("Bema");
    g.add_vertex("Hala targowa");
    g.add_vertex("Dubois");
    g.add_vertex("Botaniczny");
    g.add_vertex("Pomorska");
    g.add_edge("Bema", "Botaniczny", 2);
    g.add_edge("Bema", "Dubois", 2);
    g.add_edge("Dubois", "Pomorska", 1);
    g.add_edge("Hala targowa", "Bema", 3);
    g.print_graph();
    g.BFS("Bema","Botaniczny");
    std::cout<<std::endl;
    g.DFS("Bema","Botaniczny");
}

