#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "ClosestPairs/SweepLine.hpp"
#include "ClosestPairs/SweepLine.cpp"
#include <iostream>

using namespace std;

string gridsBaseDir = "data/grids/";

int main() {
    cout << "Hello, World!" << endl;

    // Generate grids
    // bulkGenerateGrids(gridsBaseDir);

    // Load grid
    /*
    for (int i = 5; i <= 50; i += 5) {
        string filename = gridsBaseDir + to_string(i) + ".bin";
        Grid grid = loadGrid(filename);
        printGrid(grid);
    }
    */
    Grid grid = generateGrid(1000);

    float mindistance = findClosestPoints(grid);
    float mindistance2 = closestPairForced(grid);

    //print each distance
    cout << "The closest pair of points in the grid is: " << mindistance << endl;
    cout << "The closest pair of points in the grid is: " << mindistance2 << endl;


}
