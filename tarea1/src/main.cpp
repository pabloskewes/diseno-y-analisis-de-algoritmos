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

RTree generate_nearest_x_binary(int power, int M) {
    string sample_file = "data/rectangles/input_" + to_string(power) + ".txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);

    cout << "Number of rectangles: " << rectangles.size() << endl;

    cout << "Building R-tree..." << endl;
    RTree rtree1 = RTree::bulkLoad(M, rectangles, BulkLoadingAlgorithm::NearestX);

    cout << "Printing root node..." << endl;
    rtree1.root->print();

    cout << "Height: " << rtree1.getHeight() << endl;

    cout << "Computing nodes offset..." << endl;

    rtree1.computeNodesOffset();

    // cout << "Printing offsets..." << endl;

    // cout << "Root offset: " << rtree1.root->offset << endl;
    // cout << "Root children offsets: " << endl;
    // for (Node *child : rtree1.root->children) {
    //     cout << child->offset << endl;
    // }

    // string output_file = "data/btrees/nearestx_" + to_string(power) + ".bin";
    // rtree1.setNodesLocation(output_file);
    // rtree1.saveNodesToDisk();

    return rtree1;
}

int main() {
    optimize();

    // Computing right size for M
    int B = 4096; // 4KB: block size

    int node_size =
        sizeof(bool) + // 1 byte for is_leaf
        sizeof(long long) + // 8 bytes for offset
        sizeof(int) +        // 4 bytes for num_rectangles
        sizeof(int);       // 4 bytes for num_children

    int child_size =
        sizeof(Rectangle) +
        sizeof(long long); // 32 bytes for rectangle, 8 bytes for offset

    int M = calculate_M(B, node_size, child_size);

    cout << "M=" << M << endl;

    int power = 17;

    RTree rtree1 = generate_nearest_x_binary(power, M);
    // NodeData root = rtree1.readNode(0);
    // cout << "Root: " << endl;
    // cout << "Offset: " << root.offset << endl;
    // cout << "Is leaf: " << root.is_leaf << endl;
    // cout << "Rectangles: " << endl;
    // for (Rectangle rectangle : root.rectangles) {
    //     cout << rectangle.bottom_left.x << " " << rectangle.bottom_left.y << " "
    //          << rectangle.top_right.x << " " << rectangle.top_right.y << endl;
    // }
    // cout << "Children offsets: " << endl;
    // for (long long child_offset : root.children_offsets) {
    //     cout << child_offset << endl;
    // }

    return 0;
}
