#include "rectangle/rectangle.hpp"
#include "rtree/rtree.hpp"
#include "tests/test_rectangles.hpp"

#include <iostream>
#include <cmath>



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    RTree rtree;
    rtree.sayHello();

    // test_intersect();
    // test_generate_random_rects();
    test_generate_random_rects_massive(std::pow(2, 18));

    return 0;
}
