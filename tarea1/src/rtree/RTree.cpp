#include "rtree/RTree.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/HilbertCurve.hpp"
#include "rtree/NearestX.hpp"
#include "rtree/SortTileRecursive.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

/**
 * @brief Gets the height of the RTree.
 * @return The height of the RTree.
 */
int RTree::getHeight() {
    if (!this->tree_loaded) {
        cout << "Tree not loaded" << endl;
        return -1;
    }
    int height = 0;
    Node *node = this->root;
    while (!node->is_leaf) {
        height++;
        node = node->children[0];
    }
    return height;
}

/**
 * @brief Constructs a new RTree object with the given maximum number of
 * entries per node.
 * @param M The maximum number of entries per node.
 * @param root The root node of the RTree.
 * @param tree_loaded Whether the tree is loaded in memory or not.
 * @param nodes_in_disk Whether the nodes are stored in the disk or not.
 */
RTree::RTree(int M, Node *root, bool tree_loaded) {
    this->M = M;
    this->root = root;
    this->tree_loaded = tree_loaded;
    this->nodes_file = "";
    if (fs::exists(nodes_file)) {
        this->nodes_in_disk = true;
    } else {
        this->nodes_in_disk = false;
    }
}

void RTree::sayHello() {
    cout << "Hello from Rtree!" << endl;
}

/**
 * @brief Sets the location of the nodes file.
 * @param nodes_file The location of the nodes file.
 */
void RTree::setNodesLocation(string nodes_file) {
    this->nodes_file = nodes_file;
}

long long _computeNodesOffset(Node *node, long long offset) {
    cout << "offset: " << offset << endl;
    node->offset = offset;
    offset += node->diskSize();
    for (int i = 0; i < node->children.size(); i++) {
        offset = _computeNodesOffset(node->children[i], offset);
    }
    return offset;
}

/**
 * @brief Computes the offset of each node in the file.
 */
void RTree::computeNodesOffset() {
    _computeNodesOffset(this->root, 0);
}


/**
 * @brief Creates a new RTree object with the given maximum number of entries
 * per node, containing the rectangles closest to the origin point.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @param algorithm The algorithm to use to build the RTree.
 * @return A new RTree object containing the closest rectangles.
 */
RTree RTree::bulkLoad(int M, vector<Rectangle> rectangles,
                      BulkLoadingAlgorithm algorithm) {
    Node *bulkLoadResultRoot;
    switch (algorithm) {
    case NearestX:
        bulkLoadResultRoot = nearestX(M, rectangles);
        break;
    case HilbertCurve:
        bulkLoadResultRoot = hilbertCurve(M, rectangles);
        break;
    case SortTileRecursive:
        bulkLoadResultRoot = sortTileRecursive(M, rectangles);
        break;
    default:
        throw "Invalid algorithm";
    }

    cout << "Root: " << endl;
    bulkLoadResultRoot->print();
    return RTree(M, bulkLoadResultRoot, true);
}
