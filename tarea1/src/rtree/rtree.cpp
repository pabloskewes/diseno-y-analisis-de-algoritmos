#include "rtree/rtree.hpp"
#include "rectangle/rectangle.hpp"
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
    this->rectangles = vector<Rectangle>(M);
    this->children = vector<Node *>(M);
    this->is_leaf = is_leaf;
}

/**
 * @brief Constructs a new Node object by providing all the necessary
 * information.
 * @param rectangles The rectangles contained in the node.
 * @param children The children of the node.
 * @param is_leaf Whether the node is a leaf or not.
 */
Node::Node(vector<Rectangle> rectangles, vector<Node *> children,
           bool is_leaf) {
    this->rectangles = rectangles;
    this->children = children;
    this->is_leaf = is_leaf;
}

RTree::RTree(int M) {
    this->M = M;
    // TODO: put nodes in file (NOT TXT FILE: should be binary)
}

void RTree::sayHello() {
    cout << "Hello from Rtree!" << endl;
}

/**
 * Creates a new RTree object with the given maximum number of entries per node,
 * containing the rectangles closest to the origin point.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @return A new RTree object containing the closest rectangles.
 */
RTree RTree::fromNearestX(int M, vector<Rectangle> rectangles) {
    cout << "fromNearestX" << endl;
    return RTree(M);
}

/**
 * @brief Creates an RTree from a set of rectangles using the Hilbert Curve
 * algorithm.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The set of rectangles to be inserted into the RTree.
 * @return RTree The resulting RTree.
 */
RTree RTree::fromHilbertCurve(int M, vector<Rectangle> rectangles) {
    cout << "fromHilbertCurve" << endl;
    return RTree(M);
}

/**
 * @brief Constructs an RTree recursively using the Sort-Tile-Recursive
 * algorithm.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles A vector of rectangles to be inserted into the RTree.
 * @return RTree The constructed RTree.
 */
RTree RTree::fromSortTileRecursive(int M, vector<Rectangle> rectangles) {
    cout << "fromSortTileRecursive" << endl;
    return RTree(M);
}
