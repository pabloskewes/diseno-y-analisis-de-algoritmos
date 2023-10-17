#include "rtree/RTree.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/HilbertCurve.hpp"
#include "rtree/NearestX.hpp"
#include "rtree/SortTileRecursive.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Constructs a new empty Node object, with a fixed maximum number of
 * entries per node.
 * @param M The maximum number of entries per node.
 * @param is_leaf Whether the node is a leaf or not.
 */
Node::Node(int M, bool is_leaf) {
    this->children = vector<Node *>(M);
    this->is_leaf = is_leaf;
}

/**
 * @brief Constructs a new Node object by providing all the necessary
 * information.
 * @param MBR The Minimum Bounding Rectangle of the node.
 * @param rectangles The rectangles contained in the node.
 * @param children The children of the node.
 * @param is_leaf Whether the node is a leaf or not.
 */
Node::Node(vector<Node *> children, vector<Rectangle> rectangles,
           bool is_leaf) {
    this->children = children;
    this->rectangles = rectangles;
    this->is_leaf = is_leaf;
    this->MBR = computeMBR(rectangles);
}

/**
 * @brief Prints the node to stdout: the MBR, whether it is a leaf or not, and
 * the number of children.
 */
void Node::print() {
    cout << "Node(MBR=(" << this->MBR.bottom_left.x << ", "
         << this->MBR.bottom_left.y << "), (" << this->MBR.top_right.x << ", "
         << this->MBR.top_right.y << "), is_leaf=" << this->is_leaf
         << ", num_children=" << this->children.size() << ")" << endl;
}

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
 */
RTree::RTree(int M, Node *root, bool tree_loaded) {
    this->M = M;
    this->root = root;
    this->tree_loaded = tree_loaded;
    // TODO: put nodes in file (NOT TXT FILE: should be binary)
}

void RTree::sayHello() {
    cout << "Hello from Rtree!" << endl;
}

/**
 * Creates a new RTree object with the given maximum number of entries per
 * node, containing the rectangles closest to the origin point.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @return A new RTree object containing the closest rectangles.
 */
RTree RTree::fromNearestX(int M, vector<Rectangle> rectangles) {
    Node *root = nearestX(M, rectangles);
    cout << "Root: " << endl;
    root->print();
    return RTree(M, root, true);
}

/**
 * @brief Creates an RTree from a set of rectangles using the Hilbert
 Curve
 * algorithm.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The set of rectangles to be inserted into the RTree.
 * @return RTree The resulting RTree.
 */
RTree RTree::fromHilbertCurve(int M, vector<Rectangle> rectangles) {
    Node *root = hilbertCurve(M, rectangles);
    cout << "Root: " << endl;
    root->print();
    return RTree(M, root, true);
}

/**
 * @brief Constructs an RTree recursively using the Sort-Tile-Recursive
 * algorithm.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles A vector of rectangles to be inserted into the
 RTree.
 * @return RTree The constructed RTree.
 */
RTree RTree::fromSortTileRecursive(int M, vector<Rectangle> rectangles) {
    Node *root = sortTileRecursive(M, rectangles);
    cout << "Root: " << endl;
    root->print();
    return RTree(M, root, true);
}
