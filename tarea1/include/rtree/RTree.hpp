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
    vector<Rectangle> rectangles;
    bool is_leaf;

    Node(int M, bool is_leaf);
    Node(vector<Node *> children, vector<Rectangle> rectangles, bool is_leaf);

    void print();
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

/**
 * @class RTree
 * @brief A class representing an R-tree.
 * @param root The root of the R-tree.
 * @param M The maximum number of entries per node.
 * @param file The file where the R-tree stores its nodes.
 * @param tree_loaded Whether the tree is loaded in memory or not.
 * @param nodes_in_disk Whether the nodes are stored in the disk or not.
 */
class RTree {
  public:
    Node *root;
    int M;
    string nodes_file;
    bool tree_loaded;
    bool nodes_in_disk;

    RTree(int M, Node *root, bool tree_loaded);

    void sayHello();
    int getHeight();
    void setNodesLocation(string nodes_file);
    void saveNodesToDisk();
    NodeData readNode(long long offset);

    static RTree fromNearestX(int M, vector<Rectangle> rectangles);
    static RTree fromHilbertCurve(int M, vector<Rectangle> rectangles);
    static RTree fromSortTileRecursive(int M, vector<Rectangle> rectangles);
};

#endif
