#ifndef DIVIDEANDCONQUER_HPP
#define DIVIDEANDCONQUER_HPP

#include "Grid/Grid.hpp"
#include <vector>

using namespace std;

/**
 * @brief Compute the distance between two points using the Divide and Conquer algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
float closestPairDivideAndConquer(Grid &grid);


#endif // DIVIDEANDCONQUER_HPP