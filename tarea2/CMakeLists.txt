cmake_minimum_required(VERSION 3.10)

project(Sorting)

include_directories(include)

add_executable(
    Sorting 
    src/main.cpp
)

target_link_libraries(Sorting)
