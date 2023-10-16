#include "rtree/HilbertCurve.hpp"
#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

Node hilbertCurve(int M, vector<Rectangle> rectangles) {

    cout << "HilbertCurve" << endl;
    return Node(M, false);
}