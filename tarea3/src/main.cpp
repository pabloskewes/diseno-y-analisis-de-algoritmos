#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "Hashing/LinkedList.hpp"
#include "Hashing/Hashing.hpp"
#include "ClosestPairs/SweepLine.cpp"
#include "ClosestPairs/Randomized.hpp"
#include <iostream>

using namespace std;

string gridsBaseDir = "data/grids/";

int main() {
    cout << "Hello, World!" << endl;

    Hashing<int> hash;
    hash.insert(1, 10);
    hash.insert(2, 20);
    hash.insert(3, 30);
    hash.insert(4, 40);
    hash.insert(5, 50);
    hash.insert(6, 60);
    hash.insert(7, 70);
    hash.insert(8, 80);
    hash.insert(9, 90);
    hash.insert(10, 100);

    hash.print();

    hash.printStats();

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
