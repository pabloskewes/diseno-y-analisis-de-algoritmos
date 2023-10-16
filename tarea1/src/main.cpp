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

    string sample_file = "data/rectangles/input_15.txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);
    RTree::fromSortTileRecursive(100, rectangles);

    NodeData node_data = {0, true, std::vector<Rectangle>(),
                          std::vector<long long>()};

    std::cout << "sizeof(NodeData) = " << sizeof(NodeData) << endl;
    std::cout << "sizeof(Rectangle) = " << sizeof(Rectangle) << endl;
    std::cout << "sizeof(long long) = " << sizeof(long long) << endl;
    std::cout << "sizeof(bool) = " << sizeof(bool) << endl;
    std::cout << "sizeof(int) = " << sizeof(int) << endl;
    std::cout << "sizeof(long) = " << sizeof(long) << endl;

    return 0;
}
