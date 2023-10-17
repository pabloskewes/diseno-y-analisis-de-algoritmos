#include "rtree/NearestX.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;

int recursionStep = 0;

/**
 * @brief Recursively groups nodes into a single root node, where each node has
 * M children.
 * @param M The maximum number of children a node can have.
 * @param nodes The list of nodes to group.
 * @return The root node of the RTree.
 */
Node* _nearestX(int M, vector<Node *> nodes) {

    cout << "Recursion step: " << recursionStep << endl;
    recursionStep++;

    // Iterate over nodes and group them into new nodes
    vector<Node *> new_nodes;
    for (int i = 0; i < nodes.size(); i += M) { // O(n)
        vector<Node *> children;
        vector<Rectangle> rectangles;
        for (int j = i; j < i + M && j < nodes.size(); j++) {
            Node *node = nodes[j];
            children.push_back(node);
            rectangles.push_back(node->MBR);
        }
        Node *new_node = new Node(children, rectangles, false);
        new_nodes.push_back(new_node);
    }

    // If there is only one node, return it
    if (new_nodes.size() == 1) {
        new_nodes[0]->print();
        return new_nodes[0];
    } else {
        return _nearestX(M, new_nodes);
    }
}

/**
 * @brief Uses the NearestX algorithm build the root node of the RTree.
 *
 * @param M The maximum number of children a node can have.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @return The root node of the RTree.
 * @details Given a set R of n rectangles, and M being the maximum number of
 * children for each node in the tree, the method sorts the rectangles in R
 * based on the X-coordinate of the rectangle's center. It then groups them in
 * sets of size M by using consecutive rectangles in the sorted sequence. This
 * forms M nodes, each with M children, except the last node, which may have
 * fewer children. From these M nodes, identified by rectangles (the Minimum
 * Bounding Rectangle or MBR that contains all their children), we take the
 * center again and repeat the previous method of grouping the points with this
 * new set of nodes. This process is repeated until all nodes from one iteration
 * can be grouped into a single root node.
 */
Node* nearestX(int M, vector<Rectangle> rectangles) {
    cout << "NearestX" << endl;

    // Create tuple with center of each rectangle
    vector<tuple<Rectangle, Point>> tuples;
    for (Rectangle rect : rectangles) { // O(n)
        tuple<Rectangle, Point> tuple = make_tuple(rect, middle_point(rect));
        tuples.push_back(tuple);
    }

    // Sort tuples by x-coordinate of center
    std::sort( // O(n log n)
        tuples.begin(), tuples.end(),
        [](const tuple<Rectangle, Point> &a, const tuple<Rectangle, Point> &b) {
            return get<1>(a).x < get<1>(b).x;
        });

    // Create nodes from sorted tuples
    vector<Node *> leafs;
    for (int i = 0; i < tuples.size(); i += M) { // O(n)
        vector<Rectangle> rectangles;
        for (int j = i; j < i + M && j < tuples.size(); j++) {
            tuple<Rectangle, Point> tuple = tuples[j];
            Rectangle rect = get<0>(tuple);
            rectangles.push_back(rect);
        }
        Node *leaf = new Node(vector<Node *>(), rectangles, true);
        leafs.push_back(leaf);
    }

    return _nearestX(M, leafs);
}
