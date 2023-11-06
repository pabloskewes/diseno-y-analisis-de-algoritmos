cmake_minimum_required(VERSION 3.10)

project(Sorting)

include_directories(include)

add_executable(
    Sorting 
    src/main.cpp

    src/Array/ArrayGenerator.cpp
    src/Array/isSorted.cpp

    src/SortAlgorithm/quickSort.cpp
)

target_link_libraries(Sorting)
