cmake_minimum_required(VERSION 3.10)

project(RTree)

include_directories(include)

add_executable(
    RTree 
    src/main.cpp

    # Rectangle
    src/rectangle/rectangle.cpp
    src/rectangle/test_rectangle.cpp
    src/rectangle/rect_generator.cpp

    # RTree
    src/rtree/RTree.cpp
    src/rtree/Node.cpp
    src/rtree/NearestX.cpp
    src/rtree/HilbertCurve.cpp
    src/rtree/SortTileRecursive.cpp
)

target_link_libraries(RTree)
