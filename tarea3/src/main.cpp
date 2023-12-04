#include "ClosestPairs/BruteForce.hpp"
#include "ClosestPairs/DivideAndConquer.hpp"
#include "ClosestPairs/Randomized.hpp"
#include "ClosestPairs/SweepLine.hpp"
#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "Hashing/Hashing.hpp"
#include "Hashing/LinkedList.hpp"
#include <iostream>
#include <string>
#include <tuple>

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
    // bulkGenerateGrids(gridsBaseDir);

    // Load grid
    // for (int i = 5; i <= 50; i += 5) {
    //     string filename = gridsBaseDir + to_string(i) + ".bin";
    //     Grid grid = loadGrid(filename);
    //     printGrid(grid);
    // }

    // load grid
    // Grid grid = loadGrid(gridsBaseDir + "test.bin");
    // Grid grid2 = copyGrid(grid);
    // Grid grid3 = copyGrid(grid);

    // // Brute force
    // cout << "Brute force" << endl;
    // tuple<Point, Point, float> closestPair =
    // clostestPairBruteForce(grid.points); cout << "Closest pair: (" <<
    // get<0>(closestPair).x << ", "
    //      << get<0>(closestPair).y << ") and (" << get<1>(closestPair).x << ",
    //      "
    //      << get<1>(closestPair).y << ")" << endl;
    // cout << "Distance: " << get<2>(closestPair) << endl;

    // // Divide and conquer
    // cout << "Divide and conquer" << endl;
    // closestPair = closestPairDivideAndConquer(grid2.points, 0,
    // grid2.points.size()); cout << "Closest pair: (" << get<0>(closestPair).x
    // << ", "
    //      << get<0>(closestPair).y << ") and (" << get<1>(closestPair).x << ",
    //      "
    //      << get<1>(closestPair).y << ")" << endl;
    // cout << "Distance: " << get<2>(closestPair) << endl;

    // // Sweep line
    // cout << "Sweep line" << endl;
    // closestPair = closestPairSweepLine(grid3.points);
    // cout << "Closest pair: (" << get<0>(closestPair).x << ", "
    //      << get<0>(closestPair).y << ") and (" << get<1>(closestPair).x << ",
    //      "
    //      << get<1>(closestPair).y << ")" << endl;
    // cout << "Distance: " << get<2>(closestPair) << endl;

    Grid grid = loadGrid(gridsBaseDir + "test.bin");
    float d = closestPairRandomized(grid, 50);
    cout << "d: " << d << endl;

    // cout << grid << endl;

    return 0;
}
