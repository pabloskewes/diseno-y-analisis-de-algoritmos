#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
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

    std::string toString() const {
        return "Point(x=" + std::to_string(x) + ", y=" + std::to_string(y) +
               ")";
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << p.toString();
        return os;
    }
};

/**
 * @struct Grid
 * @brief A struct representing a grid with a set of points and a set of edges.
 * @param points A vector of points.
 */
struct Grid {
    vector<Point> points;

    Grid() {
    }

    Grid(vector<Point> points) {
        this->points = points;
    }

    string toString(int head = 5, int tail = 5) const {
        string s = "Grid(points=[";
        int n = points.size();
        for (int i = 0; i < min(n, head); i++) {
            s += points[i].toString() + ", ";
        }
        if (n > head + tail) {
            s += "..., ";
        }
        for (int i = max(n - tail, head); i < n; i++) {
            s += points[i].toString() + ", ";
        }
        s += "])";
        return s;
    }

    friend std::ostream &operator<<(std::ostream &os, const Grid &grid) {
        os << grid.toString();
        return os;
    }
};

Grid loadGrid(string filename);
void writeGrid(Grid grid, string filename);
Grid generateGrid(int n);
Grid mergeGrids(vector<Grid *> grids);
void printGrid(Grid grid, int head = 5, int tail = 5);
Grid copyGrid(Grid grid);

#endif
