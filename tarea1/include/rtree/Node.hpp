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
 * @param offset The corresponding offset in the file where the node is stored:
 * -1 if the node is not stored in the file.
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
 * @param offset The offset of the node in the file.
 * @param is_leaf Whether the node is a leaf or not.
 * @param num_children The number of children of the node.
 * @param rectangles The rectangles contained in the node.
 * @param children_offsets The offsets of the children of the node in the file.
 */
struct NodeData {
    long long offset;
    bool is_leaf;
    int num_children;
    vector<Rectangle> rectangles;
    vector<long long> children_offsets;
};

#endif // NODE_HPP
