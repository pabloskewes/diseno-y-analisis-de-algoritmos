#include "Grid/Grid.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @brief Compute the distance between two points
 *
 * @param p1 First point
 * @param p2 Second point
 * @return float Distance between the two points
 */
float euclideanDistance(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param grid Grid of points
 * @param left Left index of the grid
 * @param right Right index of the grid
 * @return Tuple containing the closest pair of points and the distance between
 * them
 */
tuple<Point, Point, float> clostestPairBruteForce(const vector<Point> &points,
                                                  int left, int right) {
    float minDistance = numeric_limits<float>::infinity();
    Point p1, p2;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            float distance = euclideanDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return make_tuple(p1, p2, minDistance);
}

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param grid Grid of points
 * @return Tuple containing the closest pair of points and the distance between
 * them
 */
tuple<Point, Point, float> clostestPairBruteForce(const vector<Point> &points) {
    return clostestPairBruteForce(points, 0, points.size());
}