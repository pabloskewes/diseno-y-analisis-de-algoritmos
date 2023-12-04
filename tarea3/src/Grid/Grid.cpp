#include "Grid/Grid.hpp"
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

/**
 * @brief Generates a random float between min and max.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random float between min and max.
 */
float randomFloat(float min, float max) {
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

/**
 * @brief Generates a grid with n points.
 * @param n The number of points to generate.
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @return A grid with n points.
 */
Grid generateGrid(int n, float width, float height) {
    Grid grid;
    for (int i = 0; i < n; i++) {
        Point point;
        point.x = randomFloat(0, width);
        point.y = randomFloat(0, height);
        grid.points.push_back(point);
    }
    return grid;
}

/**
 * @brief Generates a grid with n points on a [0, 1] x [0, 1] grid.
 * @param n The number of points to generate.
 * @return A grid with n points.
 */
Grid generateGrid(int n) {
    return generateGrid(n, 1, 1);
}

/**
 * @brief Writes a grid to a file with the given filename in binary.
 * @param grid The grid to write.
 * @param filename The filename to write to.
 */
void writeGrid(Grid grid, string filename) {
    ofstream file(filename, ios::out | ios::binary);
    int n = grid.points.size();
    file.write((char *)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        file.write((char *)&grid.points[i].x, sizeof(float));
        file.write((char *)&grid.points[i].y, sizeof(float));
    }
    file.close();
}

/**
 * @brief Loads a grid from a file with the given filename in binary.
 * @param filename The filename to load from.
 * @return The grid loaded from the file.
 */
Grid loadGrid(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    int n;
    file.read((char *)&n, sizeof(int));
    Grid grid;
    for (int i = 0; i < n; i++) {
        Point point;
        file.read((char *)&point.x, sizeof(float));
        file.read((char *)&point.y, sizeof(float));
        grid.points.push_back(point);
    }
    file.close();
    return grid;
}

/**
 * @brief Copies a grid.
 * @param grid The grid to copy.
 * @return A copy of the grid.
 */
Grid copyGrid(Grid grid) {
    Grid copy;
    copy.points = grid.points;
    return copy;
}

/**
 * @brief Prints a grid to stdout.
 * @param grid The grid to print.
 */
void printGrid(Grid grid, int head, int tail) {
    int n = grid.points.size();
    cout << "Grid with " << n << " points:" << endl;
    for (int i = 0; i < head; i++) {
        cout << "(" << grid.points[i].x << ", " << grid.points[i].y << ")"
             << endl;
    }
    cout << "..." << endl;
    for (int i = n - tail; i < n; i++) {
        cout << "(" << grid.points[i].x << ", " << grid.points[i].y << ")"
             << endl;
    }
}