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

/**
 * @brief Creates a new RTree object with the given maximum number of entries
 * per node, containing the rectangles closest to the origin point.
 *
 * @param M The maximum number of entries per node.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @param algorithm The algorithm to use to build the RTree.
 * @return A new RTree object containing the closest rectangles.
 */
RTree RTree::bulkLoad(int M, vector<Rectangle> rectangles,
                      BulkLoadingAlgorithm algorithm) {
    Node *bulkLoadResultRoot;
    switch (algorithm) {
    case NearestX:
        bulkLoadResultRoot = nearestX(M, rectangles);
        break;
    case HilbertCurve:
        bulkLoadResultRoot = hilbertCurve(M, rectangles);
        break;
    case SortTileRecursive:
        bulkLoadResultRoot = sortTileRecursive(M, rectangles);
        break;
    default:
        throw "Invalid algorithm";
    }

    cout << "Root: " << endl;
    bulkLoadResultRoot->print();
    return RTree(M, bulkLoadResultRoot, true);
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

long long _computeNodesOffset(Node *node, long long offset) {
    node->offset = offset;
    offset += node->diskSize();
    for (int i = 0; i < node->children.size(); i++) {
        offset = _computeNodesOffset(node->children[i], offset);
    }
    return offset;
}

/**
 * @brief Computes the offset of each node in the file.
 * It traverses the tree in pre-order (DFS)
 */
void RTree::computeNodesOffset() {
    _computeNodesOffset(this->root, 0);
}

void _writeNodesToDisk(Node *node, ofstream &output_file) {
    long long offset = node->offset;
    bool is_leaf = node->is_leaf;
    int num_rectangles = node->rectangles.size();
    int num_children = node->children.size();
    vector<Rectangle> rectangles = node->rectangles;
    vector<long long> children_offsets;
    for (int i = 0; i < node->children.size(); i++) {
        children_offsets.push_back(node->children[i]->offset);
    }

    output_file.write((char *)&offset, sizeof(offset));
    output_file.write((char *)&is_leaf, sizeof(is_leaf));
    output_file.write((char *)&num_rectangles, sizeof(num_rectangles));
    output_file.write((char *)&num_children, sizeof(num_children));
    for (int i = 0; i < rectangles.size(); i++) {
        output_file.write((char *)&rectangles[i], sizeof(rectangles[i]));
    }
    for (int i = 0; i < children_offsets.size(); i++) {
        output_file.write((char *)&children_offsets[i],
                          sizeof(children_offsets[i]));
    }

    for (int i = 0; i < node->children.size(); i++) {
        _writeNodesToDisk(node->children[i], output_file);
    }
}

/**
 * @brief Writes the nodes of the RTree to the disk.
 * @param file The file where the nodes will be written.
 */
void RTree::writeNodesToDisk(string file) {
    ofstream output_file(file, ios::out | ios::binary);
    if (!output_file.is_open()) {
        throw "Could not open file";
    }

    Node *root = this->root;
    if (root->offset != 0) {
        throw "Root offset must be 0";
    }

    _writeNodesToDisk(root, output_file);

    output_file.close();
    this->nodes_file = file;
    this->nodes_in_disk = true;
}

/**
 * @brief Reads a node from the disk.
 * @param offset The offset of the node in the file.
 * @return The node read from the disk.
 */
NodeData RTree::readNodeFromDisk(long long offset) {
    if (!this->nodes_in_disk) {
        throw "Nodes not in disk";
    }

    ifstream input_file(this->nodes_file, ios::in | ios::binary);
    if (!input_file.is_open()) {
        throw "Could not open file";
    }

    input_file.seekg(offset);

    NodeData node_data;
    input_file.read((char *)&node_data.offset, sizeof(node_data.offset));
    input_file.read((char *)&node_data.is_leaf, sizeof(node_data.is_leaf));
    input_file.read((char *)&node_data.num_rectangles,
                    sizeof(node_data.num_rectangles));
    input_file.read((char *)&node_data.num_children,
                    sizeof(node_data.num_children));

    for (int i = 0; i < node_data.num_rectangles; i++) {
        Rectangle rectangle;
        input_file.read((char *)&rectangle, sizeof(rectangle));
        node_data.rectangles.push_back(rectangle);
    }

    for (int i = 0; i < node_data.num_children; i++) {
        long long child_offset;
        input_file.read((char *)&child_offset, sizeof(child_offset));
        node_data.children_offsets.push_back(child_offset);
    }

    input_file.close();

    return node_data;
}

bool _checkNodesInMemoryEqualNodesInDisk(RTree *rtree, Node *node) {
    NodeData node_data = rtree->readNodeFromDisk(node->offset);
    if (node->is_leaf != node_data.is_leaf) {
        return false;
    }
    if (node->rectangles.size() != node_data.rectangles.size()) {
        return false;
    }
    if (node->children.size() != node_data.children_offsets.size()) {
        return false;
    }
    for (int i = 0; i < node->rectangles.size(); i++) {
        Rectangle rectangle_node = node->rectangles[i];
        Rectangle rectangle_node_data = node_data.rectangles[i];
        if (rectangle_node.bottom_left.x != rectangle_node_data.bottom_left.x ||
            rectangle_node.bottom_left.y != rectangle_node_data.bottom_left.y ||
            rectangle_node.top_right.x != rectangle_node_data.top_right.x ||
            rectangle_node.top_right.y != rectangle_node_data.top_right.y) {

            return false;
        }
    }
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->offset != node_data.children_offsets[i]) {
            return false;
        }
    }
    for (int i = 0; i < node->children.size(); i++) {
        if (!_checkNodesInMemoryEqualNodesInDisk(rtree, node->children[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks if the nodes in memory are equal to the nodes in the disk.
 * @return Whether the nodes in memory are equal to the nodes in the disk.
 */
bool RTree::checkNodesInMemoryEqualNodesInDisk() {
    return _checkNodesInMemoryEqualNodesInDisk(this, this->root);
}