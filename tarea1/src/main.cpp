#include "rectangle/rectangle.hpp"
#include "rectangle/rect_generator.hpp"
#include "rectangle/test_rectangle.hpp"
#include "rtree/rtree.hpp"

#include <cmath>
#include <iostream>
#include <random>

using namespace std;

void optimize() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

void generate_R_sets() {
    int first_power = 10;
    int last_power = 25;
    for (int i = first_power; i <= last_power; i++) {
        generate_input_samples(i);
    }
}

int main() {
    optimize();

    int B = 4096; // 4KB: block size
    // int M = 1000;

    // test_intersect();
    // test_generate_random_rects();
    // test_generate_random_rects_massive(std::pow(2, 20));
    // test_write_and_read_rects(100);
    // generate_R_sets();

    NodeData node_data = {0, true, std::vector<Rectangle>(),
                          std::vector<long long>()};

    cout << "size of long long: " << sizeof(long long) << endl;
    cout << "size of bool: " << sizeof(bool) << endl;
    cout << "size of vector<Rectangle>: " << sizeof(std::vector<Rectangle>)
    << endl; cout << "size of Rectangle: " << sizeof(Rectangle) << endl; cout
    << "size of NodeData: " << sizeof(node_data) << endl;

    return 0;
}
