#ifndef HILBERT_CURVE_HPP
#define HILBERT_CURVE_HPP

#include "rectangle/rectangle.hpp"
#include "rtree/RTree.hpp"
#include <vector>

using namespace std;

long long hilbertValue(Point point, long long n);
Node* hilbertCurve(int M, vector<Rectangle> rectangles);

#endif // NEAREST_X_HPP