#ifndef RTREE_HPP
#define RTREE_HPP

#include "rectangle/rectangle.hpp"
#include <fstream>
#include <vector>

using namespace std;

/**
 * @class Node
 * @brief A class representing a node in the R-tree.
 * @param MBR The Minimum Bounding Rectangle of the node.
 * @param children The children of the node.
 * @param is_leaf Whether the node is a leaf or not.
 */
class Node {
  public:
    Rectangle MBR;
    vector<Node *> children;
    bool is_leaf;

    Node(int M, bool is_leaf);
    Node(Rectangle MBR, std::vector<Node *> children, bool is_leaf);

    void print();
};

/**
 * @struct NodeData
 * @brief A struct representing the data of a node in the R-tree that is stored
 * in the file (i.e. not in memory)
 * @param offset The offset of the node in the file.
 * @param MBR The Minimum Bounding Rectangle of the node.
 * @param is_leaf Whether the node is a leaf or not.
 * @param children_offsets The offsets of the children of the node in the file.
 */
struct NodeData {
    long long offset;
    Rectangle MBR;
    bool is_leaf;
    vector<long long> children_offsets;
};

/**
 * @class RTree
 * @brief A class representing an R-tree.
 */
class RTree {
  public:
    Node *root;
    int M;
    fstream file;

    RTree(int M);

    void sayHello();

    static RTree fromNearestX(int M, vector<Rectangle> rectangles);
    static RTree fromHilbertCurve(int M, vector<Rectangle> rectangles);
    static RTree fromSortTileRecursive(int M, vector<Rectangle> rectangles);
};

#endif
