#ifndef DIVIDEANDCONQUER_HPP
#define DIVIDEANDCONQUER_HPP

#include "Grid/Grid.hpp"
#include <vector>

using namespace std;

/**
 * @brief Compute the distance between two points
 *
 * @param p1 First point
 * @param p2 Second point
 * @return float Distance between the two points
 */
tuple<Point, Point, float> closestPairDivideAndConquer(vector<Point> &points,
                                                       int left, int right);

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param points Vector of points
 * @return Tuple containing the closest pair of points and the distance between
 * them
 */
tuple<Point, Point, float> closestPairDivideAndConquer(vector<Point> &points);

#endif // DIVIDEANDCONQUER_HPP