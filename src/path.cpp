#include "../lib/path.h"

void Path::print_path() const {
    for (const auto &node: path) {
        std::cout << node.name << " (";
        for(const auto& line: node.tram_lines)
            std::cout << line << " ";
        std::cout << ")" << std::endl;
    }
    std::cout << std::endl << "Path length: " << path_length << std::endl;
    std::cout << "Enqueuings: " << enqueuings << std::endl;
    std::cout << "Extensions: " << extensions << std::endl;
}

void Path::export_path(std::string filename) const {
    std::ofstream path_coords(filename);
    for(const auto& vertex: path) {
        path_coords << vertex.longitude << "," << vertex.latitude << std::endl;
    }
    path_coords.close();
}

void Path::set_extensions(const int& extensions) {
    this->extensions = extensions;
}

void Path::set_enqueuings(const int& enqueuings) {
    this->enqueuings = enqueuings;
}