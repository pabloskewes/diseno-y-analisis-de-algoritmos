#include "ClosestPairs/Randomized.hpp"
#include "Grid/Grid.hpp"
#include <algorithm>
#include <random>


using namespace std;

/*
* Function to select n random points from the grid
* @param grid A Grid struct representing a grid with a set of points and a set of edges.
* @return A smaller grid with n random points from the original grid.
*/

Grid selectRandomPoints(const Grid& grid, int n) {
    Grid newGrid;
    newGrid.points.reserve(n);
    newGrid.edges.reserve(n);
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

Grid selectRandomPoints(Grid originalGrid, int n) {
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
