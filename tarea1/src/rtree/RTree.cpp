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

/**
 * @brief Saves the nodes of the RTree to the nodes file.
 * If the nodes file does not exist, it is created, otherwise it is overwritten.
 * If the nodes file is not set, an error is thrown.
 */
void RTree::saveNodesToDisk() {
    if (this->nodes_file == "") {
        throw "Nodes file not set";
    }
    ofstream nodes_stream(this->nodes_file, ios::binary);
    if (!nodes_stream.is_open()) {
        throw "Could not open nodes file";
    }
    vector<NodeData> nodes_data;
    vector<Node *> nodes;
    nodes.push_back(this->root);
    while (!nodes.empty()) {
        Node *node = nodes.back();
        nodes.pop_back();
        NodeData node_data;
        node_data.offset = nodes_stream.tellp();
        node_data.is_leaf = node->is_leaf;
        node_data.rectangles = node->rectangles;
        for (Node *child : node->children) {
            if (child != nullptr) {
                node_data.children_offsets.push_back(nodes_stream.tellp());
                nodes.push_back(child);
            } else {
                node_data.children_offsets.push_back(-1);
            }
        }
        nodes_data.push_back(node_data);
    }
    for (NodeData node_data : nodes_data) {
        nodes_stream.write((char *)&node_data.offset, sizeof(long long));
        nodes_stream.write((char *)&node_data.is_leaf, sizeof(bool));
        int num_rectangles = node_data.rectangles.size();
        nodes_stream.write((char *)&num_rectangles, sizeof(int));
        for (Rectangle rectangle : node_data.rectangles) {
            nodes_stream.write((char *)&rectangle.bottom_left.x,
                               sizeof(long long));
            nodes_stream.write((char *)&rectangle.bottom_left.y,
                               sizeof(long long));
            nodes_stream.write((char *)&rectangle.top_right.x,
                               sizeof(long long));
            nodes_stream.write((char *)&rectangle.top_right.y,
                               sizeof(long long));
        }
        for (long long child_offset : node_data.children_offsets) {
            nodes_stream.write((char *)&child_offset, sizeof(long long));
        }
    }
    nodes_stream.close();
}

/**
 * @brief Reads a node from the nodes file.
 * @param offset The offset of the node in the nodes file.
 * @return NodeData The node data struct read from the nodes file.
 */
NodeData RTree::readNode(long long offset) {
    ifstream nodes_stream(this->nodes_file, ios::binary);
    if (!nodes_stream.is_open()) {
        throw "Could not open nodes file";
    }
    nodes_stream.seekg(offset);
    NodeData node_data;
    nodes_stream.read((char *)&node_data.offset, sizeof(long long));
    nodes_stream.read((char *)&node_data.is_leaf, sizeof(bool));
    int num_rectangles;
    nodes_stream.read((char *)&num_rectangles, sizeof(int));
    for (int i = 0; i < num_rectangles; i++) {
        Rectangle rectangle;
        nodes_stream.read((char *)&rectangle.bottom_left.x, sizeof(long long));
        nodes_stream.read((char *)&rectangle.bottom_left.y, sizeof(long long));
        nodes_stream.read((char *)&rectangle.top_right.x, sizeof(long long));
        nodes_stream.read((char *)&rectangle.top_right.y, sizeof(long long));
        node_data.rectangles.push_back(rectangle);
    }
    for (int i = 0; i < this->M; i++) {
        long long child_offset;
        nodes_stream.read((char *)&child_offset, sizeof(long long));
        node_data.children_offsets.push_back(child_offset);
    }
    nodes_stream.close();
    return node_data;
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
