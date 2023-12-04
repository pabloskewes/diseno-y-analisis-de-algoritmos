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

    Point p1 = {1, 2};
    Point p2 = {3, 4};
    Point p3 = {5, 6};
    Point p4 = {7, 8};

    Hashing<Point> hash1;
    hash1.insert(1, p1);
    hash1.insert(2, p2);
    hash1.insert(1, p3);
    hash1.insert(2, p4);

    hash1.print();
    hash.printStats();
    Point el = hash.get(1);
    cout << el << endl;

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
