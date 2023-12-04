#include "ClosestPairs/BruteForce.hpp"
#include "Grid/Grid.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

/**
 * @brief Compute the distance between two points
 *
 * @param p1 First point
 * @param p2 Second point
 * @return float Distance between the two points
 */
tuple<Point, Point, float> closestPairDivideAndConquer(vector<Point> &points,
                                                       int left, int right) {
    if (right - left <= 3) {
        return clostestPairBruteForce(points, left, right);
    }

    int mid = (left + right) / 2;
    tuple<Point, Point, float> leftMin =
        closestPairDivideAndConquer(points, left, mid);
    tuple<Point, Point, float> rightMin =
        closestPairDivideAndConquer(points, mid, right);
    float minDistance = min(get<2>(leftMin), get<2>(rightMin));

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - points[mid].x) < minDistance) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1;
             j < strip.size() && (strip[j].y - strip[i].y) < minDistance; ++j) {
            float distance = euclideanDistance(strip[i], strip[j]);
            if (distance < minDistance) {
                minDistance = distance;
                get<0>(leftMin) = strip[i];
                get<1>(leftMin) = strip[j];
                get<2>(leftMin) = minDistance;
            }
        }
    }

    return leftMin;
}

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param points Vector of points
 * @return Tuple containing the closest pair of points and the distance between
 * them
 */
tuple<Point, Point, float> closestPairDivideAndConquer(vector<Point> &points) {
    sort(points.begin(), points.end(), compareX);
    return closestPairDivideAndConquer(points, 0, points.size());
}
