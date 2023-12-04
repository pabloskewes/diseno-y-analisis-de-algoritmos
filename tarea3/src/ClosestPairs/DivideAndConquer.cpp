#include "ClosestPairs/BruteForce.hpp"
#include "Grid/Grid.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

using namespace std;

/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}
/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
float bruteForce(vector<Point>& points, int left, int right) {
    float minDistance = numeric_limits<float>::infinity();
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            minDistance = min(minDistance, euclideanDistance(points[i], points[j]));
        }
    }
    return minDistance;
}
/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
float closestPairUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        return bruteForce(points, left, right);
    }

    int mid = (left + right) / 2;
    float leftMin = closestPairUtil(points, left, mid);
    float rightMin = closestPairUtil(points, mid, right);
    float minDistance = min(leftMin, rightMin);


    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - points[mid].x) < minDistance) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDistance; ++j) {
            minDistance = min(minDistance, euclideanDistance(strip[i], strip[j]));
        }
    }

    return minDistance;
}
/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
float closestPairDivideAndConquer(Grid& grid) {
    sort(grid.points.begin(), grid.points.end(), compareX);
    return closestPairUtil(grid.points, 0, grid.points.size());
}