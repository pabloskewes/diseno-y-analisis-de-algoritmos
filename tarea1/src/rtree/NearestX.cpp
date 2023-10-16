#include "rtree/NearestX.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

struct NodeTuple {
    Node *node;
    Point center;
};

int recursionStep = 0;

/**
 * @brief Computes the Minimum Bounding Rectangle of a set of rectangles.
 * @param M The maximum number of children a node can have.
 * @param rectangles The vector of rectangles to compute the MBR from.
 * @return The MBR of the rectangles.
 */

Node _nearestX(int M, vector<Node *> nodes) {

    cout << "Recursion step: " << recursionStep << endl;
    recursionStep++;

    vector<NodeTuple> tuples;
    for (Node *node : nodes) { // O(n)
        NodeTuple tuple;
        tuple.node = node;
        tuple.center = middle_point(node->MBR);
        tuples.push_back(tuple);
    }
    cout << "Created " << tuples.size() << " tuples." << endl;

    sort(tuples.begin(), tuples.end(), // O(n log n)
         [](NodeTuple a, NodeTuple b) { return a.center.x < b.center.x; });

    cout << "Printing first 5 ordered tuples" << endl;
    for (int i = 0; i < 5; i++) {
        NodeTuple tuple = tuples[i];
        cout << "Tuple " << i << endl;
        cout << "Center: (" << tuple.center.x << ", " << tuple.center.y << ")"
             << endl;
        print_rectangle(tuple.node->MBR);
    }

    cout << "Printing last 5 ordered tuples" << endl;
    for (int i = tuples.size() - 5; i < tuples.size(); i++) {
        NodeTuple tuple = tuples[i];
        cout << "Tuple " << i << endl;
        cout << "Center: (" << tuple.center.x << ", " << tuple.center.y << ")"
             << endl;
        print_rectangle(tuple.node->MBR);
    }

    vector<Node *> new_nodes;
    for (int i = 0; i < tuples.size(); i += M) { // O(n)
        vector<Node *> children;
        vector<Rectangle> rectangles;
        for (int j = i; j < i + M && j < tuples.size(); j++) {
            Node *child = tuples[j].node;
            children.push_back(child);
            rectangles.push_back(child->MBR);
        }

        Rectangle MBR = computeMBR(rectangles);
        Node parent = Node(MBR, children, false);
        new_nodes.push_back(&parent);
    }

    if (new_nodes.size() == 1) {
        return *new_nodes[0];
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
Node nearestX(int M, vector<Rectangle> rectangles) {
    cout << "NearestX" << endl;

    // Create a node (leaf) for each rectangle in the set
    vector<Node *> nodes;
    for (Rectangle rect : rectangles) {
        Node *node = new Node(rect, vector<Node *>(), true);
        nodes.push_back(node);
    }

    // cout << "Created " << nodes.size() << " nodes." << endl;
    // // print first 5 nodes
    // for (int i = 0; i < 5; i++) {
    //     Node *node = nodes[i];
    //     Rectangle MBR = node->MBR;
    //     cout << "Node " << i << endl;
    //     print_rectangle(MBR);
    // }

    return _nearestX(M, nodes);
}
