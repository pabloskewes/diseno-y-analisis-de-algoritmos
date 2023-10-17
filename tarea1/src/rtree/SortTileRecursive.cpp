#include "rtree/SortTileRecursive.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

Node *sortTileRecursive(int M, vector<Rectangle> rectangles) {

    cout << "SortTileRecursive" << endl;
    Node *dummy = new Node(M, false);
    return dummy;
}