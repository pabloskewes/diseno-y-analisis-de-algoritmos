#ifndef NODE_HPP
#define NODE_HPP

#include "rectangle/rectangle.hpp"
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
    vector<Rectangle> rectangles;
    bool is_leaf;
    long long offset;

    Node(vector<Node *> children, vector<Rectangle> rectangles, bool is_leaf);

    void print();
    int diskSize();
};

/**
 * @struct NodeData
 * @brief A struct representing the data of a node in the R-tree that is stored
 * in the file (i.e. not in memory)
 * @param offset The offset of the node in the file. (8 bytes)
 * @param is_leaf Whether the node is a leaf or not. (1 byte)
 * @param rectangles The rectangles contained in the node. (32 bytes each)
 * @param children_offsets The offsets of the children of the node in the file. (8 bytes each)
 * @details The size of the struct is 8 + 1 + 32 * num_rectangles + 8 * num_children
 */
struct NodeData {
    long long offset;
    bool is_leaf;
    int num_rectangles;
    int num_children;
    vector<Rectangle> rectangles;
    vector<long long> children_offsets;
};

#endif // NODE_HPP
