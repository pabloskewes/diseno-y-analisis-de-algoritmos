cmake_minimum_required(VERSION 3.10)

project(Hashing)

include_directories(include)

add_executable(
    Hashing

    src/main.cpp

    src/Grid/Grid.cpp
    src/Grid/bulkGeneration.cpp

    src/ClosestPairs/SweepLine.cpp
    src/ClosestPairs/Randomized.cpp

    src/Hashing/Hashing.cpp
)

target_link_libraries(Hashing)
