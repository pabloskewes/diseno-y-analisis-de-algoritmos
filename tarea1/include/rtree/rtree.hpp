#ifndef RTREE_HPP
#define RTREE_HPP

#include "rectangle/rectangle.hpp"
#include <fstream>
#include <vector>

using namespace std;

/**
 * @class Node
 * @brief A class representing a node in the R-tree.
 */
class Node {
  public:
    vector<Node *> children;
    vector<Rectangle> rectangles;
    bool is_leaf;

    Node(int M, bool is_leaf);
    Node(std::vector<Rectangle> rectangles, std::vector<Node *> children,
         bool is_leaf);
};

/**
 * @struct NodeData
 * @brief A struct representing the data of a node in the R-tree that is stored
 * in the file (i.e. not in memory)
 */
struct NodeData {
    long long offset;
    bool is_leaf;
    vector<Rectangle> rectangles;
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
