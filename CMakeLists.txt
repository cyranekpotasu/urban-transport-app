cmake_minimum_required(VERSION 3.9)
project(UrbanTransportApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/)

add_executable(UrbanTransportApp main.cpp lib/graph.h src/graph.cpp lib/path.h lib/vertex.h src/path.cpp)
