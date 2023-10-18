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
}

/**
 * @brief Prints the node to stdout: the MBR, whether it is a leaf or not, and
 * the number of children.
 */
void Node::print() {
    cout << "Node(MBR=(" << this->MBR.bottom_left.x << ", "
         << this->MBR.bottom_left.y << "), (" << this->MBR.top_right.x << ", "
         << this->MBR.top_right.y << "), is_leaf=" << this->is_leaf
         << ", num_children=" << this->children.size()
         << ", disk_size=" << this->diskSize() << ")" << endl;
}

/**
 * @brief Computes the size that the node would take in the disk.
 * @return The size of the node.
 * @details The size of the node is:
 * 1 byte for is_leaf
 * 8 bytes for offset
 * 4 bytes for num_children
 * 4 bytes for num_rectangles
 * 32 bytes for each rectangle
 * 8 bytes for each offset
 */
int Node::diskSize() {
    int metadata_size = sizeof(this->is_leaf) + sizeof(this->offset) +
                        sizeof(int) + // 4 bytes for num_children
                        sizeof(int);  // 4 bytes for num_rectangles
    int rectangles_size = this->rectangles.size() *
                          sizeof(Rectangle); // 32 bytes for each rectangle
    int children_size =
        this->children.size() * sizeof(long long); // 8 bytes for each offset
    return metadata_size + rectangles_size + children_size;
}
