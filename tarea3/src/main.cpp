#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "Hashing/Hashing.hpp"
#include "ClosestPairs/SweepLine.cpp"
#include "ClosestPairs/Randomized.hpp"
#include <iostream>

using namespace std;

string gridsBaseDir = "data/grids/";

int main() {
    cout << "Hello, World!" << endl;

    Hashing<string> hash;
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "three");
    hash.insert(4, "four");
    hash.insert(5, "five");
    hash.insert(6, "six");
    hash.insert(7, "seven");
    hash.insert(8, "eight");
    hash.insert(9, "nine");
    hash.insert(10, "ten");

    hash.print();

    hash.printStats();

    string el = hash.get(5);
    cout << el << endl;

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
