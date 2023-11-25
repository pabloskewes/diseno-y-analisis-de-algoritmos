cmake_minimum_required(VERSION 3.10)

project(Hashing)

include_directories(include)

add_executable(
    Hashing
    src/main.cpp
)

target_link_libraries(Hashing)
