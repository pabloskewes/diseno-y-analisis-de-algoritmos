#include "rtree/SortTileRecursive.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;

int recursionStepSortTileRecursive = 0;

/**
 * @brief Recursively groups nodes into a single root node, where each node has
 * M children.
 * @param M The maximum number of children a node can have.
 * @param nodes The list of nodes to group.
 * @param S The number of groups created in the previous step.
 * @return The root node of the RTree.
 */
Node *_sortTileRecursive(int M, vector<Node *> nodes, int S) {

    cout << "Sort-Tile-Recursive recursion step "
         << recursionStepSortTileRecursive++ << endl;

    int n = nodes.size();

    // Group nodes into S groups of size M*S over the x-axis
    vector<vector<Node *>> groups;
    for (int i = 0; i < n; i += M * S) { // O(n)
        vector<Node *> group;
        for (int j = i; j < i + M * S && j < n; j++) {
            group.push_back(nodes[j]);
        }
        groups.push_back(group);
    }
    // Group each group into S groups of size M over the y-axis
    vector<vector<vector<Node *>>> groups2;
    for (int i = 0; i < groups.size(); i++) { // O(n)
        vector<vector<Node *>> group2;
        for (int j = 0; j < groups[i].size(); j += M) {
            vector<Node *> group3;
            for (int k = j; k < j + M && k < groups[i].size(); k++) {
                group3.push_back(groups[i][k]);
            }
            group2.push_back(group3);
        }
        groups2.push_back(group2);
    }

    // Create nodes from each group (S*S nodes)
    vector<Node *> new_nodes;  
    for (int i = 0; i < groups2.size(); i++) { // O(n)
        for (int j = 0; j < groups2[i].size(); j++) {
            vector<Node *> children;
            vector<Rectangle> rectangles;
            for (int k = 0; k < groups2[i][j].size(); k++) {
                Node *node = groups2[i][j][k];
                children.push_back(node);
                rectangles.push_back(node->MBR);
            }
            Node *new_node = new Node(children, rectangles, false);
            new_nodes.push_back(new_node);
        }
    }

    // If there is only one node, return it
    if (new_nodes.size() == 1) {
        cout << "Root node:" << endl;
        new_nodes[0]->print();
        return new_nodes[0];
    } else {
        return _sortTileRecursive(M, new_nodes, S);
    }


}
/**
 * @brief Uses the Sort-Tile-Recursive algorithm build the root node of the
 * RTree.
 *
 * @param M The maximum number of children a node can have.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @return The root node of the RTree.
 * @details Given a set R of n rectangles, The method starts by sorting the
 * n reference points according to their X coordinate, dividing the result
 * into S = M groups with M · S nodes each, where M is the necessary number
 * of leaves in the tree to store all the nodes. Each of the S groups is
 * then sorted again according to their Y coordinate, and then divided into
 * S groups of size M. This process results in S · S = M new nodes, which
 * are grouped recursively using the same method, constantly reducing the
 * number of nodes until they can all be joined into a single root node.
 */
Node *sortTileRecursive(int M, vector<Rectangle> rectangles) {
    cout << "Creating RTree with Sort-Tile-Recursive algorithm..." << endl;

    int n = rectangles.size();
    int S = (int)ceil(sqrt(n / M));

    // Create tuples of (rectangle, center)
    vector<tuple<Rectangle, Point>> tuples;
    for (int i = 0; i < rectangles.size(); i++) {
        Rectangle rectangle = rectangles[i];
        Point center = middle_point(rectangle);
        tuples.push_back(make_tuple(rectangle, center));
    }

    // Sort tuples by x-coordinate of center
    std::sort( // O(n log n)
        tuples.begin(), tuples.end(),
        [](const tuple<Rectangle, Point> &a, const tuple<Rectangle, Point> &b) {
            return get<1>(a).x < get<1>(b).x;
        });

    // Group tuples into S groups of size M*S
    vector<vector<tuple<Rectangle, Point>>> groups;
    for (int i = 0; i < tuples.size(); i += M * S) {
        vector<tuple<Rectangle, Point>> group;
        for (int j = i; j < i + M * S && j < tuples.size(); j++) {
            group.push_back(tuples[j]);
        }
        groups.push_back(group);
    }

    // Sort each group by y-coordinate of center
    for (int i = 0; i < groups.size(); i++) {
        std::sort( // O(n log n)
            groups[i].begin(), groups[i].end(),
            [](const tuple<Rectangle, Point> &a,
               const tuple<Rectangle, Point> &b) {
                return get<1>(a).y < get<1>(b).y;
            });
    }

    // Group each group into S groups of size M
    vector<vector<vector<tuple<Rectangle, Point>>>> groups2;
    for (int i = 0; i < groups.size(); i++) {
        vector<vector<tuple<Rectangle, Point>>> group2;
        for (int j = 0; j < groups[i].size(); j += M) {
            vector<tuple<Rectangle, Point>> group3;
            for (int k = j; k < j + M && k < groups[i].size(); k++) {
                group3.push_back(groups[i][k]);
            }
            group2.push_back(group3);
        }
        groups2.push_back(group2);
    }

    // Create nodes from each group (S*S leaf nodes)
    vector<Node *> leafs;
    for (int i = 0; i < groups2.size(); i++) {
        for (int j = 0; j < groups2[i].size(); j++) {
            vector<Rectangle> rectangles;
            for (int k = 0; k < groups2[i][j].size(); k++) {
                tuple<Rectangle, Point> tuple = groups2[i][j][k];
                Rectangle rect = get<0>(tuple);
                rectangles.push_back(rect);
            }
            Node *leaf = new Node(vector<Node *>(), rectangles, true);
            leafs.push_back(leaf);
        }
    }

    return _sortTileRecursive(M, leafs, S);

}