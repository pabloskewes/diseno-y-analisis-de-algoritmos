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

RTree saveBtreeBin(int power, BulkLoadingAlgorithm algorithm, int M) {
    string sample_file = "data/rectangles/input_" + to_string(power) + ".txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);

    cout << "Number of rectangles: " << rectangles.size() << endl;

    cout << "Building R-tree..." << endl;
    RTree rtree = RTree::bulkLoad(M, rectangles, algorithm);

    cout << "Printing root node..." << endl;
    rtree.root->print();

    cout << "Height: " << rtree.getHeight() << endl;

    cout << "Computing nodes offset..." << endl;

    rtree.computeNodesOffset();

    string base_name = "data/btrees/";
    switch (algorithm) {
    case NearestX:
        base_name += "nearest_x/";
        break;
    case HilbertCurve:
        base_name += "hilbert_curve/";
        break;
    case SortTileRecursive:
        base_name += "sort_tile_recursive/";
        break;
    default:
        throw "Invalid algorithm";
    }

    string file_name = base_name + "pow_" + to_string(power) + ".bin";
    rtree.writeNodesToDisk(file_name);

    return rtree;
}

int main() {
    optimize();

    // Computing right size for M
    int B = 4096; // 4KB: block size

    int node_size = sizeof(bool) +      // 1 byte for is_leaf
                    sizeof(long long) + // 8 bytes for offset
                    sizeof(int) +       // 4 bytes for num_rectangles
                    sizeof(int);        // 4 bytes for num_children

    int child_size =
        sizeof(Rectangle) +
        sizeof(long long); // 32 bytes for rectangle, 8 bytes for offset

    int M = calculate_M(B, node_size, child_size);

    cout << "M=" << M << endl;

    int power = 17;

    RTree rtree = saveBtreeBin(power, NearestX, M);
    bool success = rtree.checkNodesInMemoryEqualNodesInDisk();

    if (success) {
        cout << "Nodes in memory and in disk are equal" << endl;
    } else {
        cout << "Nodes in memory and in disk are not equal" << endl;
    }

    return 0;
}
