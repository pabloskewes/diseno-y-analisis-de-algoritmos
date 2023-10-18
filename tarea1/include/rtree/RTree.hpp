#ifndef RTREE_HPP
#define RTREE_HPP

#include "rectangle/rectangle.hpp"
#include "rtree/Node.hpp"
#include <fstream>
#include <vector>

using namespace std;


enum BulkLoadingAlgorithm {
    NearestX,
    HilbertCurve,
    SortTileRecursive,
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

    static RTree bulkLoad(int M, vector<Rectangle> rectangles,
                          BulkLoadingAlgorithm algorithm);
};

#endif
