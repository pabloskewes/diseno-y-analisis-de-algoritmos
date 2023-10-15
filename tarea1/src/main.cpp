#include "rectangle/rectangle.hpp"
#include "rectangle/test_rectangle.hpp"
#include "rtree/rtree.hpp"

#include <cmath>
#include <iostream>
#include <random>

void optimize() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    optimize();

    int M = 1000;

    // test_intersect();
    test_generate_random_rects();
    // test_generate_random_rects_massive(std::pow(2, 18));

    return 0;
}
