
#include "ClosestPairs/Randomized.hpp"
#include "Grid/Grid.hpp"
#include "Hashing/Hashing.hpp"
#include "ClosestPairs/SweepLine.cpp"
#include <algorithm>
#include <random>


using namespace std;

/*
* Function to select n random points from the grid
* @param grid A Grid struct representing a grid with a set of points and a set of edges.
* @return A smaller grid with n random points from the original grid.
*/

Grid selectRandomPoints1(const Grid& grid, int n) {
    Grid newGrid;
    newGrid.points.reserve(n);
    vector<int> randomPoints = randomInts(0, grid.points.size() - 1, n);
    for (int i = 0; i < n; i++) {
        newGrid.points.push_back(grid.points[randomPoints[i]]);
    }
    return newGrid;
}

vector<int> randomInts(int min, int max, int n) {
    vector<int> randomInts;
    randomInts.reserve(n);
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dist(min, max);
    for (int i = 0; i < n; i++) {
        randomInts.push_back(dist(g));
    }
    return randomInts;
}
/*
* Function to select n random points from the grid
* @param grid A Grid struct representing a grid with a set of points and a set of edges.
* @return A smaller grid with n random points from the original grid.
*/

Grid selectRandomPoints2(Grid originalGrid, int n) {
    // Check if n is greater than the total number of points in the original grid
    n = min(n, static_cast<int>(originalGrid.points.size()));

    // Shuffle the points randomly
    random_device rd;
    mt19937 g(rd());
    shuffle(originalGrid.points.begin(), originalGrid.points.end(), g);

    // Create a new grid with the first n points from the shuffled list
    Grid selectedGrid;
    selectedGrid.points.assign(originalGrid.points.begin(), originalGrid.points.begin() + n);

    return selectedGrid;
}

/*
* Function to get the respective grid it belongs
* @param Point A Point struct representing a point in the grid.
* @param d size of the fracturing grid
*/

int getNumberGrid(Point point, int d) {
    float x = point.x;
    float y = point.y;
    int gridX = x / d;
    int gridY = y / d;
    int numberOfGrids = 1 / d;
    return ((numberOfGrids + 1) * (gridX + 1)) + gridY + 1;
}

/*
* Function to get the minimun distances between every point from 2 grid
* @param grid1 first grid
* @param grid2 second grid
* @param d size of the potencial minimun distance
*/

float minDistance2grids(const Grid& grid1, const Grid& grid2, float d) {
    float minDistance = d;
    for (int i = 0; i < grid1.points.size(); i++) {
        for (int j = 0; j < grid2.points.size(); j++) {
            float distance = distanceSquare(grid1.points[i], grid2.points[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    return minDistance;
}

/*
* Function to get the minimun distances between every point from 1 grid
* @param grid1 first grid
* @param d size of the potencial minimun distance
*/

float minDistance1grid(const Grid& grid, float d) {
    float minDistance = d;
    for (int i = 0; i < grid.points.size(); i++) {
        for (int j = i + 1; j < grid.points.size(); j++) {
            float distance = distanceSquare(grid.points[i], grid.points[j]);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    return minDistance;
}


/*
* Final function that using random points, it returns a potencion d, then it divides the grid in d*d grids, 
* later on we save every point using a hash function, finally we go through every grid and we check if there is a point that is closer than the potencial d
* @param grid A Grid struct representing a grid with a set of points and a set of edges.
* @param hashFunction A hash function that saves the points in a hash table.
* @param n Number of random points to select.
*/
float closestPairRandomized(const Grid& grid, Hash hashFunction, int n) {
    // Select n random points from the grid
    Grid selectedGrid = selectRandomPoints2(grid, n);

    // Calculate the potential d
    float d = sweepLine(selectedGrid);

    // Divide the grid in d*d grids
    int numberVerticalGrids = (1 / d) + 1;
    int numberTotalGrids = numberVerticalGrids * numberVerticalGrids;

    // Going through every point and saving it in a hash table
    for (int i = 0; i < selectedGrid.points.size(); i++) {
        Point point = selectedGrid.points[i];
        int gridNumber = getNumberGrid(point, d);
        //*use the hashfunction to save the point in the hash table
        //hashFunction.insert(gridNumber, point);
    }
    
    
    // Go through every grid and check if there is a point that is closer than the potencial d
    for (i = 1; i < numberTotalGrids; i++){
        if (i > (numberTotalGrids - numberVerticalGrids)){
            // probamos con su misma grilla y con la de al lado
            Grid ownGrid = hashFunction.getGrid(i);
            Grid leftGrid = hashFunction.getGrid(i + 1);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);
        }
        else if (i%numberVerticalGrids == 0){
            // probamos con su misma grilla y con la de arriba y arriba -1
            Grid ownGrid = hashFunction.getGrid(i);
            Grid upGrid = hashFunction.getGrid(i + numberVerticalGrids);
            Grid upLeftGrid = hashFunction.getGrid(i + numberVerticalGrids - 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upLeftGrid, d);
            d = minDistance1grid(ownGrid, d);
        }
        else if (i%numberVerticalGrids == 1){
            // probamos con su misma grilla y con la de arriba, arriba +1 y la de al lado
            Grid ownGrid = hashFunction.getGrid(i);
            Grid upGrid = hashFunction.getGrid(i + numberVerticalGrids);
            Grid upRightGrid = hashFunction.getGrid(i + numberVerticalGrids + 1);
            Grid leftGrid = hashFunction.getGrid(i + 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upRightGrid, d);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);
        }
        else {
            // probamos con su misma grilla y con la de arriba, arriba +1, arriba -1 y la de al lado
            Grid ownGrid = hashFunction.getGrid(i);
            Grid upGrid = hashFunction.getGrid(i + numberVerticalGrids);
            Grid upLeftGrid = hashFunction.getGrid(i + numberVerticalGrids - 1);
            Grid upRightGrid = hashFunction.getGrid(i + numberVerticalGrids + 1);
            Grid leftGrid = hashFunction.getGrid(i + 1);
            d = minDistance2grids(ownGrid, upGrid, d);
            d = minDistance2grids(ownGrid, upLeftGrid, d);
            d = minDistance2grids(ownGrid, upRightGrid, d);
            d = minDistance2grids(ownGrid, leftGrid, d);
            d = minDistance1grid(ownGrid, d);

        }
    }
    
    return d;
}