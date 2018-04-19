#ifndef URBANTRANSPORTAPP_PATH_H
#define URBANTRANSPORTAPP_PATH_H

#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include "vertex.h"

class Path {
    std::deque<Vertex> path;
    int path_length = 0;
    int extensions = 0;
    int enqueuings = 0;

public:
    Path() = default;
    Path(const std::deque<Vertex> _path, int length): path(_path), path_length(length) {}

    void print_path() const;
    void export_path(std::string filename) const;
    void set_extensions(const int& extensions);
    void set_enqueuings(const int& enqueuings);
    void check_transitions() const;

};

#endif //URBANTRANSPORTAPP_PATH_H
