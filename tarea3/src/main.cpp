#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "Hashing/Hashing.hpp"
#include "Hashing/LinkedList.hpp"
#include "ClosestPairs/BruteForce.hpp"
#include "ClosestPairs/SweepLine.hpp"
#include <iostream>

using namespace std;

string gridsBaseDir = "data/grids/";

int main() {
    cout << "Hello, World!!!" << endl;

    // Hashing<string> hash;
    // hash.insert(1, "one");
    // hash.insert(2, "two");
    // hash.insert(3, "three");
    // hash.insert(4, "four");
    // hash.insert(5, "five");
    // hash.insert(6, "six");
    // hash.insert(7, "seven");
    // hash.insert(8, "eight");
    // hash.insert(9, "nine");
    // hash.insert(10, "ten");

    // hash.print();

    // hash.printStats();

    // string el = hash.get(5);
    // cout << el << endl;

    // Generate grids
    bulkGenerateGrids(gridsBaseDir);

    // Load grid
    // for (int i = 5; i <= 50; i += 5) {
    //     string filename = gridsBaseDir + to_string(i) + ".bin";
    //     Grid grid = loadGrid(filename);
    //     printGrid(grid);
    // }

    // load grid
    Grid grid = loadGrid(gridsBaseDir + "50.bin");

}
