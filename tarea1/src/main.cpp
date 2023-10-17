#include "rectangle/rect_generator.hpp"
#include "rectangle/rectangle.hpp"
#include "rectangle/test_rectangle.hpp"
#include "rtree/RTree.hpp"

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

int calculate_M(int B, int node_size, int child_size) {
    return (B - node_size) / child_size;
}

int main() {
    optimize();

    int B = 4096; // 4KB: block size
    int node_size = sizeof(bool) +
                    sizeof(long long); // 1 byte for is_leaf, 8 bytes for offset
    int child_size =
        sizeof(Rectangle) +
        sizeof(long long); // 32 bytes for rectangle, 8 bytes for offset
    int M = calculate_M(B, node_size, child_size);

    cout << "M=" << M << endl;

    // test_intersect();
    // test_generate_random_rects();
    // test_generate_random_rects_massive(std::pow(2, 20));
    // test_write_and_read_rects(100);
    // test_computeMBR();
    // generate_R_sets();
    int power = 24;

    string sample_file = "data/rectangles/input_" + to_string(power) + ".txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);

    cout << "Number of rectangles: " << rectangles.size() << endl;
    // print first 5 rectangles
    for (int i = 0; i < 5; i++) {
        print_rectangle(rectangles[i]);
    }

    cout << "Building R-tree..." << endl;
    // RTree rtree1 = RTree::fromNearestX(M, rectangles);
    // hilbert tree
    RTree rtree1 = RTree::fromHilbertCurve(M, rectangles);

    cout << "Printing root node..." << endl;
    rtree1.root->print();

    cout << "Height: " << rtree1.getHeight() << endl;

    return 0;
}
