#include "../lib/path.h"

void Path::print_path() const {
    print_transitions();
    std::cout << std::endl << "Path length: " << path_length << std::endl;
    std::cout << "Enqueueings: " << enqueuings << std::endl;
    std::cout << "Extensions: " << extensions << std::endl;
    std::cout << std::endl;
    for (const auto &node: path) {
        std::cout << node.name << " ";
        for(const auto& line: node.tram_lines)
            std::cout << line << " ";
        std::cout << std::endl;
    }
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

std::vector<Path::Transition> Path::check_transitions() const {
    auto it = path.begin();
    std::vector<Transition> transitions {};
    while (it != path.cend()) {
        std::string curr_name = (*it).name;
        auto intersection = (*it).tram_lines;
        Vertex current_stop = *it;
        while(!intersection.empty() && ++it != path.cend()) {
            auto tmp = std::set<std::string> {};
            auto next = (*it);
            std::set_intersection(current_stop.tram_lines.cbegin(),
                                  current_stop.tram_lines.cend(),
                                  next.tram_lines.cbegin(), next.tram_lines.cend(),
                                  std::inserter(tmp, tmp.begin()));
            if(tmp.empty()) {
                it--;
                break;
            }
            intersection = std::move(tmp);
            curr_name = next.name;
        }
        transitions.emplace_back(std::make_pair(curr_name, intersection));
    }
    return transitions;
}

void Path::print_transitions() const {
    auto transitions = check_transitions();
    auto start = path[0].name;
    for (const auto& transition: transitions) {
        std::cout << start << " -> " << transition.first;
        for(const auto& line: transition.second)
            std::cout << " " << line;
        std::cout << std::endl;
        start = transition.first;
    }
}
