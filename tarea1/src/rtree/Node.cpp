#include "rtree/Node.hpp"

#include <iostream>

using namespace std;

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
    this->offset = offset;
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
 * @brief Computes the size that the node would take in the disk.
 * @return The size of the node.
 */
int Node::diskSize() {
    int metadata_size = sizeof(this->is_leaf) + sizeof(this->offset);
    int rectangles_size = this->rectangles.size() * sizeof(Rectangle);
    int children_size = this->children.size() * sizeof(long long);
    return metadata_size + rectangles_size + children_size;
}