#include "rtree/rtree.hpp"
#include "rectangle/rectangle.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Node::Node(vector<Rectangle> rectangles, bool is_leaf, Node *parent) {
    this->rectangles = rectangles;
    this->is_leaf = is_leaf;
    this->parent = parent;
}

RTree::RTree(int M) {
    this->M = M;
    this->root = new Node(vector<Rectangle>(), true, NULL);
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
 * @brief Creates an RTree from a set of rectangles using the Hilbert Curve algorithm.
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
 * @brief Constructs an RTree recursively using the Sort-Tile-Recursive algorithm.
 * 
 * @param M The maximum number of entries per node.
 * @param rectangles A vector of rectangles to be inserted into the RTree.
 * @return RTree The constructed RTree.
 */
RTree RTree::fromSortTileRecursive(int M, vector<Rectangle> rectangles) {
    cout << "fromSortTileRecursive" << endl;
    return RTree(M);
}
