#ifndef GRID_HPP
#define GRID_HPP

#include <string>
#include <vector>

using namespace std;

/**
 * @struct Point
 * @brief A struct representing a point in a 2D plane with x and y coordinates.
 */
struct Point {
    float x;
    float y;

    bool operator<(const Point &p) const {
        if (x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
};

/**
 * @struct Grid
 * @brief A struct representing a grid with a set of points and a set of edges.
 * @param points A vector of points.
 */
struct Grid {
    vector<Point> points;
};

Grid loadGrid(string filename);
void writeGrid(Grid grid, string filename);
Grid generateGrid(int n);
void printGrid(Grid grid, int head = 5, int tail = 5);
Grid copyGrid(Grid grid);

#endif
