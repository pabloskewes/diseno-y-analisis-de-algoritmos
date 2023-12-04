#ifndef SWEEPLINE_HPP
#define SWEEPLINE_HPP

#include "Grid/Grid.hpp"

using namespace std;

/**
 * @brief Compute the distance between two points using the Sweepline algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
tuple<Point, Point, float> closestPairSweepLine(vector<Point> &coordinates,
                                                int n);

/**
 * @brief Compute the distance between two points using the Sweepline algorithm
 *
 * @param coordinates Vector of points
 * @return tuple<Point, Point, float> Tuple containing the closest pair of
 * points and the distance between them
 */
tuple<Point, Point, float> closestPairSweepLine(vector<Point> &coordinates);

/**
 * @brief Find the closest pair of points in a grid using brute force
 *
 * @param grid Grid of points
 * @return float Distance between the closest pair of points
 */
tuple<Point, Point, float> closestPairSweepLine(Grid &grid);

#endif
