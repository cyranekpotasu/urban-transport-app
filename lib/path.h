#ifndef URBANTRANSPORTAPP_PATH_H
#define URBANTRANSPORTAPP_PATH_H

#include <iostream>
#include <deque>
#include "vertex.h"

class Path {
    std::deque<Vertex> path;
    int path_length;

public:
    Path(const std::deque<Vertex> _path, int length): path(_path), path_length(length) {}

    void print_path() const;

};

#endif //URBANTRANSPORTAPP_PATH_H
