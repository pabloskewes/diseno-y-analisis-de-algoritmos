#include "rtree/HilbertCurve.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;

/**
 * @brief Auxiliary function to rotate a point.
 * @param n The size of the space.
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param rx The rotation of the point.
 * @param ry The rotation of the point.
 */

void rotate(int n, int *x, int *y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            *x = n - 1 - *x;
            *y = n - 1 - *y;
        }
        // Swap x and y
        int temp = *x;
        *x = *y;
        *y = temp;
    }
}

/**
 * @brief Calculates the Hilbert value of a point.
 * @param point The point to calculate the Hilbert value of.
 * @return The Hilbert value of the point.
 */

long long hilbertValue(Point point, long long n) {

    long long hilbertVal = 0;
    int x = point.x;
    int y = point.y;
    long long s = n / 2;

    while (s > 0) {
        int rx = (x & s) > 0;
        int ry = (y & s) > 0;
        hilbertVal += s * s * ((3 * rx) ^ ry);
        rotate(s, &x, &y, rx, ry);
        s /= 2;
    }

    return hilbertVal;
}

/**
 * @brief Recursively groups nodes into a single root node, where each node
 has
 * M children.
 * @param M The maximum number of children a node can have.
 * @param nodes The list of nodes to group.
 * @return The root node of the RTree.
 */

Node *_hilbertCurve(int M, vector<Node *> nodes) {
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
        return new_nodes[0];
    } else {
        return _hilbertCurve(M, new_nodes);
    }
}

/**
 * @brief Uses the hilbertCurve algorithm build the root node of the RTree.
 *
 * @param M The maximum number of children a node can have.
 * @param rectangles The list of rectangles to insert into the RTree.
 * @return The root node of the RTree.
 * @details Given a set R of n rectangles, and M being the maximum number of
 * children for each node in the tree, the method sorts the rectangles in R
 * based on the value of the Curva de Hilbert of the rectangle's center. It then
 * groups them in sets of size M by using consecutive rectangles in the sorted
 * sequence. This forms M nodes, each with M children, except the last node,
 * which may have fewer children. From these M nodes, identified by rectangles
 * (the Minimum Bounding Rectangle or MBR that contains all their children), we
 * take the center again and repeat the previous method of grouping the points
 * with this new set of nodes. This process is repeated until all nodes from one
 * iteration can be grouped into a single root node.
 */
Node *hilbertCurve(int M, vector<Rectangle> rectangles) {

    long long n = 500000;

    // Create tuple with center of each rectangle and their Hilbert values
    long long i = 0;
    vector<tuple<Rectangle, long long>> tuples;
    for (Rectangle rect : rectangles) { // O(n)
        Point realCenter = middle_point(rect);
        Point center = {round(realCenter.x), round(realCenter.y)};
        long long hilbertVal = hilbertValue(center, n); //

        // Adjust the order as needed tuple
        tuple<Rectangle, long long> tuple = make_tuple(rect, hilbertVal);
        tuples.push_back(tuple);
    }

    // Sort tuples by Hilbert values
    std::sort( // O(n log n)
        tuples.begin(), tuples.end(),
        [](const tuple<Rectangle, long long> &a,
           const tuple<Rectangle, long long> &b) {
            return get<1>(a) < get<1>(b);
        });

    // Create nodes from sorted tuples
    vector<Node *> leafs;
    for (int i = 0; i < tuples.size(); i += M) { // O(n)
        vector<Rectangle> rectangles;
        for (int j = i; j < i + M && j < tuples.size(); j++) {
            tuple<Rectangle, long long> tuple = tuples[j];
            Rectangle rect = get<0>(tuple);
            rectangles.push_back(rect);
        }
        Node *leaf = new Node(vector<Node *>(), rectangles, true);
        leafs.push_back(leaf);
    }

    return _hilbertCurve(M, leafs);
}
