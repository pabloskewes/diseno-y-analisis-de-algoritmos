#include "ClosestPairs/BruteForce.hpp"
#include "ClosestPairs/DivideAndConquer.hpp"
#include "Grid/Grid.hpp"
#include "Hashing/Hashing.hpp"
#include "libs/progressbar.hpp"
#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <random>

using namespace std;

random_device rd2;
mt19937 g(rd2());

/**
 * Function to select n random pairs from the grid (allowing repetitions of
 * pairs). A pair cannot be formed by the same point.
 * @param grid A Grid struct representing a grid with a set of points and a set
 * of edges.
 * @return A smaller grid with n random points from the original grid.
 */
vector<tuple<Point, Point>> selectRandomPairs(const Grid &grid, int n) {
    vector<tuple<Point, Point>> pairs;
    uniform_int_distribution<> dis(0, grid.points.size() - 1);
    int i = 0;
    while (i < n) {
        int index1 = dis(g);
        int index2 = dis(g);
        if (index1 == index2) {
            cout << "same index" << endl;
            continue;
        }
        pairs.push_back(make_tuple(grid.points[index1], grid.points[index2]));
        i++;
    }
    return pairs;
}

/**
 * Compute the size of the subgrid "d" using the random pairs
 * @param grid A Grid struct representing a grid with a set of points and a set
 * of edges.
 * @return A float representing the size of the subgrid "d"
 */
float computeSubGridSize(const Grid &grid) {
    int n = grid.points.size() / 10;
    float minDistance = numeric_limits<float>::infinity();
    vector<tuple<Point, Point>> pairs = selectRandomPairs(grid, n);
    for (auto &[point1, point2] : pairs) {
        float distance = euclideanDistance(point1, point2);
        minDistance = min(minDistance, distance);
    }
    return minDistance;
}

/**
 * Function to get the respective grid it belongs
 * @param Point A Point struct representing a point in the grid.
 * @param minDistance size of the fracturing grid
 */
int getNumberGrid(Point point, float d) {
    int gridX = ceil(point.x / d);
    int gridY = ceil(point.y / d);
    int numGrids = ceil(1 / d);
    int numberGrid = (gridY - 1) * numGrids + gridX;
    // print everything
    // cout << "gridX: " << gridX << endl;
    // cout << "gridY: " << gridY << endl;
    // cout << "numGrids: " << numGrids << endl;
    // cout << "point: " << point << endl;
    // cout << "numberGrid: " << numberGrid << endl;
    return numberGrid;
}

/**
 * Function to get the minimun distances between every point from 2 grid
 * @param grid1 first grid
 * @param grid2 second grid
 * @param minDistance size of the potencial minimun distance
 */
float minDistance2grids(const Grid &grid1, const Grid &grid2, float d) {
    float minDistance = d;
    for (int i = 0; i < grid1.points.size(); i++) { // O(n1 * n2)
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
 * @param minDistance size of the potencial minimun distance
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

Grid *getGrid(int key, Hashing<Grid *> &hash) {
    if (hash.contains(key)) {
        return hash.get(key);
    }
    Grid *grid = new Grid();
    return grid;
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
float closestPairRandomized(const Grid &grid) {
    float d = computeSubGridSize(grid);
    int numberVerticalGrids = ceil(1 / d);
    int numberTotalGrids = pow(numberVerticalGrids, 2);

    cout << "d: " << d << endl;
    cout << "numberTotalGrids: " << numberTotalGrids << endl;

    vector<Grid> grids;
    Hashing<Grid *> hash(grid.points.size());

    for (Point point : grid.points) {
        int gridNumber = getNumberGrid(point, d);
        if (hash.contains(gridNumber)) {
            cout << "gridNumber already exists" << endl;
            cout << "gridNumber: " << gridNumber << endl;
            Grid *gridOnHash = hash.get(gridNumber);
            cout << "gridOnHash: " << gridOnHash << endl;
            gridOnHash->points.push_back(point);
            continue;
        }
        cout << "new gridNumber: " << gridNumber << endl;
        Grid grid(vector<Point>{point});
        grids.push_back(grid);
        hash.insert(gridNumber, &grids.back());
    }

    hash.printValueCountsStats();
    cout << "percentage of empty grids: " << hash.getPercentageOfEmptyBuckets()
         << endl;
    hash.printStats();

    float minDistance = d;

    for (int i = 1; i < numberTotalGrids; i++) {
        if (i > (numberTotalGrids - numberVerticalGrids)) {
            // probamos con su misma grilla y con la de al lado
            Grid *ownGrid = getGrid(i, hash);
            Grid *leftGrid = getGrid(i + 1, hash);
            minDistance = minDistance2grids(*ownGrid, *leftGrid, minDistance);
            minDistance = minDistance1grid(*ownGrid, minDistance);
        } else if (i % numberVerticalGrids == 0) {
            // probamos con su misma grilla y con la de arriba y arriba -1
            Grid *ownGrid = getGrid(i, hash);
            Grid *upGrid = getGrid(i + numberVerticalGrids, hash);
            Grid *upLeftGrid = getGrid(i + numberVerticalGrids - 1, hash);
            minDistance = minDistance2grids(*ownGrid, *upGrid, minDistance);
            minDistance = minDistance2grids(*ownGrid, *upLeftGrid, minDistance);
            minDistance = minDistance1grid(*ownGrid, minDistance);
        } else if (i % numberVerticalGrids == 1) {
            Grid *ownGrid = getGrid(i, hash);
            Grid *upGrid = getGrid(i + numberVerticalGrids, hash);
            Grid *upRightGrid = getGrid(i + numberVerticalGrids + 1, hash);
            Grid *leftGrid = getGrid(i + 1, hash);
            minDistance = minDistance2grids(*ownGrid, *upGrid, minDistance);
            minDistance =
                minDistance2grids(*ownGrid, *upRightGrid, minDistance);
            minDistance = minDistance2grids(*ownGrid, *leftGrid, minDistance);
            minDistance = minDistance1grid(*ownGrid, minDistance);
        } else {
            Grid *ownGrid = getGrid(i, hash);
            Grid *upGrid = getGrid(i + numberVerticalGrids, hash);
            Grid *upLeftGrid = getGrid(i + numberVerticalGrids - 1, hash);
            Grid *upRightGrid = getGrid(i + numberVerticalGrids + 1, hash);
            Grid *leftGrid = getGrid(i + 1, hash);
            minDistance = minDistance2grids(*ownGrid, *upGrid, minDistance);
            minDistance = minDistance2grids(*ownGrid, *upLeftGrid, minDistance);
            minDistance =
                minDistance2grids(*ownGrid, *upRightGrid, minDistance);
            minDistance = minDistance2grids(*ownGrid, *leftGrid, minDistance);
            minDistance = minDistance1grid(*ownGrid, minDistance);
        }
    }
    return minDistance;
}