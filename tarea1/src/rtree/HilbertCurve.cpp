#include "rtree/HilbertCurve.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;

// /**
//  * @brief Calculates the Hilbert value of a point.
//  * @param point The point to calculate the Hilbert value of.
//  * @param order The order of the Hilbert curve.
//  * @param minPoint The minimum point of the space.
//  * @param maxPoint The maximum point of the space.
//  * @return The Hilbert value of the point.
//  */
// int hilbertValue(Point point, int order, Point minPoint, Point maxPoint) {
//     int hilbertVal = 0;
//     int x = point.x;
//     int y = point.y;
//     int s = order / 2;
//     while (s > 0) {
//         int rx = (x & s) > 0;
//         int ry = (y & s) > 0;
//         hilbertVal += s * s * ((3 * rx) ^ ry);
//         rotate(s, &x, &y, rx, ry);
//         s /= 2;
//     }
//     return hilbertVal;
// }

// int recursionStep = 0;

// /**
//  * @brief Recursively groups nodes into a single root node, where each node
//  has
//  * M children.
//  * @param M The maximum number of children a node can have.
//  * @param nodes The list of nodes to group.
//  * @return The root node of the RTree.
//  */

// Node* _hilbertCurve(int M, vector<Node *> nodes) {

//     cout << "HilbertCurve" << endl;
//     cout << "Recursion step: " << recursionStep << endl;
//     recursionStep++;

//     // Iterate over nodes and group them into new nodes
//     vector<Node *> new_nodes;
//     for (int i = 0; i < nodes.size(); i += M) { // O(n)
//         vector<Node *> children;
//         vector<Rectangle> rectangles;
//         for (int j = i; j < i + M && j < nodes.size(); j++) {
//             Node *node = nodes[j];
//             children.push_back(node);
//             rectangles.push_back(node->MBR);
//         }
//         Node *new_node = new Node(children, rectangles, false);
//         new_nodes.push_back(new_node);
//     }

//     // If there is only one node, return it
//     if (new_nodes.size() == 1) {
//         new_nodes[0]->print();
//         return new_nodes[0];
//     } else {
//         return _hilbertCurve(M, new_nodes);
//     }
// }

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
    cout << "hilbertCurve" << endl;

    // int order = 10;
    // Point minPoint = Point(0, 0);

    // // Create tuple with center of each rectangle and their Hilbert values
    // vector<tuple<Rectangle, Point, int>> tuples;
    // for (Rectangle rect : rectangles) { // O(n)
    //     Point center = middle_point(rect);
    //     int hilbertVal = hilbertValue(center, order, minPoint, maxPoint); //
    //     Adjust the order as needed tuple<Rectangle, Point, int> tuple =
    //     make_tuple(rect, center, hilbertVal); tuples.push_back(tuple);
    // }

    // // Sort tuples by Hilbert values
    // std::sort( // O(n log n)
    //     tuples.begin(), tuples.end(),
    //     [](const tuple<Rectangle, Point, int> &a, const tuple<Rectangle,
    //     Point, int> &b) {
    //         return get<2>(a) < get<2>(b);
    //     });

    // // Create nodes from sorted tuples
    // vector<Node *> leafs;
    // for (int i = 0; i < tuples.size(); i += M) { // O(n)
    //     vector<Rectangle> rectangles;
    //     for (int j = i; j < i + M && j < tuples.size(); j++) {
    //         tuple<Rectangle, Point, int> tuple = tuples[j];
    //         Rectangle rect = get<0>(tuple);
    //         rectangles.push_back(rect);
    //     }
    //     Node *leaf = new Node(vector<Node *>(), rectangles, true);
    //     leafs.push_back(leaf);
    // }

    // return _hilbertCurve(M, leafs);
    return NULL;
}
