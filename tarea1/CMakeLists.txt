cmake_minimum_required(VERSION 3.10)

project(RTree)

include_directories(include)

add_executable(
    RTree 
    src/main.cpp 
    src/rtree/rtree.cpp 
    src/rectangle/rectangle.cpp
    src/rectangle/test_rectangle.cpp
    src/rectangle/rect_generator.cpp
)

target_link_libraries(RTree)
