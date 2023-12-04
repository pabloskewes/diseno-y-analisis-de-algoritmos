#include "ClosestPairs/BruteForce.hpp"
#include "ClosestPairs/DivideAndConquer.hpp"
#include "Grid/Grid.hpp"
#include "Hashing/Hashing.hpp"
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <random>

using namespace std;

/**
 * Function to select n random points from the grid
 * @param grid A Grid struct representing a grid with a set of points and a set
 * of edges.
 * @return A smaller grid with n random points from the original grid.
 */
Grid selectRandomPoints(Grid originalGrid, int n) {
    n = min(n, static_cast<int>(originalGrid.points.size()));

    random_device rd;
    mt19937 g(rd());

    Grid grid = originalGrid;
    shuffle(grid.points.begin(), grid.points.end(), g);
    grid.points.resize(n);
    return grid;
}

/**
 * Function to get the respective grid it belongs
 * @param Point A Point struct representing a point in the grid.
 * @param d size of the fracturing grid
 */
int getNumberGrid(Point point, float d) {
    int gridX = ceil(point.x / d);
    int gridY = ceil(point.y / d);
    int numGrids = ceil(1 / d);
    return (gridX - 1) * numGrids + gridY;
}

/**
 * Function to get the minimun distances between every point from 2 grid
 * @param grid1 first grid
 * @param grid2 second grid
 * @param d size of the potencial minimun distance
 */
float minDistance2grids(const Grid &grid1, const Grid &grid2, float d) {
    float minDistance = d;
    for (int i = 0; i < grid1.points.size(); i++) {
        for (int j = 0; j < grid2.points.size(); j++) {
            float distance =
                euclideanDistance(grid1.points[i], grid2.points[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    return minDistance;
}

/**
 * Function to get the minimun distances between every point from 1 grid
 * @param grid1 first grid
 * @param d size of the potencial minimun distance
 */
float minDistance1grid(const Grid &grid, float d) {
    float minDistance = d;
    for (int i = 0; i < grid.points.size(); i++) {
        for (int j = i + 1; j < grid.points.size(); j++) {
            float distance = euclideanDistance(grid.points[i], grid.points[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    return minDistance;
}

/**
 * Final function that using random points, it returns a potencion d, then
 * it divides the grid in d*d grids, later on we save every point using a
 * hash function, finally we go through every grid and we check if there is
 * a point that is closer than the potencial d
 * @param grid A Grid struct representing a grid with a set of points and a
 * set of edges.
 * @param hashFunction A hash function that saves the points in a hash
 * table.
 * @param n Number of random points to select.
 */
float closestPairRandomized(const Grid &grid, int n) {
    // Select n random points from the grid
    Grid selectedGrid = selectRandomPoints(grid, n);

    // Calculate the potential d
    float d = closestPairDivideAndConquer(selectedGrid);

    cout << "d: " << d << endl;

    // Divide the grid in d*d grids
    int numberVerticalGrids = ceil(1 / d);
    int numberTotalGrids = pow(numberVerticalGrids, 2);

    //cout << "numberVerticalGrids: " << numberVerticalGrids << endl;
    //cout << "numberTotalGrids: " << numberTotalGrids << endl;

    Hashing<Grid> hash;

    for (int i = 0; i < numberTotalGrids; i++) {
        hash.insert(i+1, Grid());
    }
    //hash.print();

    for (Point point : grid.points) {
        int gridNumber = getNumberGrid(point, d);
        Grid &gridOnHash = hash.get(gridNumber);
        gridOnHash.points.push_back(point);
    }

    // hash.printStats();

    for (int i = 1; i < numberTotalGrids; i++) {
        if (i > (numberTotalGrids - numberVerticalGrids)) {
            // probamos con su misma grilla y con la de al lado
            Grid &ownGrid = hash.get(i);
            Grid &leftGrid = hash.get(i + 1);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);
        } else if (i % numberVerticalGrids == 0) {
            // probamos con su misma grilla y con la de arriba y arriba -1
            Grid &ownGrid = hash.get(i);
            Grid &upGrid = hash.get(i + numberVerticalGrids);
            Grid &upLeftGrid = hash.get(i + numberVerticalGrids - 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upLeftGrid, d);
            d = minDistance1grid(ownGrid, d);
        } else if (i % numberVerticalGrids == 1) {
            Grid &ownGrid = hash.get(i);
            Grid &upGrid = hash.get(i + numberVerticalGrids);
            Grid &upRightGrid = hash.get(i + numberVerticalGrids + 1);
            Grid &leftGrid = hash.get(i + 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upRightGrid, d);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);
        } else {
            Grid &ownGrid = hash.get(i);
            Grid &upGrid = hash.get(i + numberVerticalGrids);
            Grid &upLeftGrid = hash.get(i + numberVerticalGrids - 1);
            Grid &upRightGrid = hash.get(i + numberVerticalGrids + 1);
            Grid &leftGrid = hash.get(i + 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upLeftGrid, d);
            d = minDistance2grids(ownGrid, upRightGrid, d);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);
        }
    }

    return d;
}
