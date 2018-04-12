#include "../lib/path.h"

void Path::print_path() const {
    for (const auto &node: path) {
        std::cout << node.name << "(";
        for(const auto& line: node.tram_lines)
            std::cout << line << " ";
        std::cout << " -> ";
    }
    std::cout << std::endl << "Path length: " << path_length << std::endl;
}
