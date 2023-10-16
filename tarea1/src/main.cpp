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

int main() {
    optimize();

    int B = 4096; // 4KB: block size
    int node_size =
        sizeof(Rectangle) + sizeof(bool) + sizeof(long long); // 41 bytes
    int M = (B - node_size) / sizeof(long long); // (B - 41) / 8 = 506
    cout << "M=" << M << endl;

    // test_intersect();
    // test_generate_random_rects();
    // test_generate_random_rects_massive(std::pow(2, 20));
    // test_write_and_read_rects(100);
    // test_computeMBR();
    // generate_R_sets();

    string sample_file = "data/rectangles/input_15.txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);

    // cout << "Number of rectangles: " << rectangles.size() << endl;
    // // print first 5 rectangles
    // for (int i = 0; i < 5; i++) {
    //     print_rectangle(rectangles[i]);
    // }

    cout << "Building R-tree..." << endl;
    RTree rtree1 = RTree::fromNearestX(M, rectangles);

    Node root = *rtree1.root;
    Rectangle MBR = root.MBR;
    root.print();

    for (int i = 0; i < M; i++) {
        cout << "Child " << i << endl;
        Node *child = root.children[i];
        Rectangle MBR = child->MBR;
    }

    // get tree height
    int height = 1;
    Node *node = rtree1.root;
    while (!node->is_leaf) {
        node = node->children[0];
        height++;
    }
    cout << "Height: " << height << endl;

    // NodeData node_data = {0, rectangles[0], true, {10, 20, 30}};

    return 0;
}
