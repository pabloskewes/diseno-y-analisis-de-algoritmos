#include "rtree/NearestX.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

Node nearestX(int M, vector<Rectangle> rectangles) {

    cout << "NearestX" << endl;
    return Node(M, false);
}