#include "Grid/Grid.hpp"
#include <iostream>

using namespace std;

string filename = "data/grids/grid_100.bin";

int main() {
    cout << "Hello, World!" << endl;

    Grid generatedGrid = generateGrid(10000);
    writeGrid(generatedGrid, filename);
    Grid loadedGrid = loadGrid(filename);

    bool equal = true;
    for (int i = 0; i < generatedGrid.points.size(); i++) {
        if (generatedGrid.points[i].x != loadedGrid.points[i].x ||
            generatedGrid.points[i].y != loadedGrid.points[i].y) {
            equal = false;
            break;
        }
    }

    cout << "Equal: " << equal << endl;
}
