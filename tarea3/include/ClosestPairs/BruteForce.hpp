#ifndef BRUTEFORCE_HPP
#define BRUTEFORCE_HPP

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
float euclideanDistance(const Point &p1, const Point &p2);

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
                                                  int left, int right);

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param grid Grid of points
 * @return Tuple containing the closest pair of points and the distance between
 * them
 */
tuple<Point, Point, float> clostestPairBruteForce(const vector<Point> &points);

#endif // BRUTEFORCE_HPP
