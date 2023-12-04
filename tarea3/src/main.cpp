#include "ClosestPairs/BruteForce.hpp"
#include "ClosestPairs/DivideAndConquer.hpp"
#include "ClosestPairs/Randomized.hpp"
#include "ClosestPairs/SweepLine.hpp"
#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include "Hashing/Hashing.hpp"
#include "Hashing/LinkedList.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

string gridsBaseDir = "data/grids/";

void runDeterministicExperiment(int from, int to, int experimentNumber) {
    for (int i = from; i <= to; i += 5) {
        string filename = gridsBaseDir + to_string(i) + ".bin";
        Grid grid = loadGrid(filename);
        cout << "Grid size: " << i << endl;

        auto start = chrono::high_resolution_clock::now();
        float d = closestPairDivideAndConquer(grid);
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(end - start);

        cout << "Divide and conquer: " << duration.count() << " microseconds"
             << endl;

        string outputFilename = "data/results/divideAndConquer/n_" +
                                to_string(i) + "exp_" +
                                to_string(experimentNumber) + ".csv";
        ofstream outputFile(outputFilename, ios::out | ios::app);
        outputFile << i << "," << duration.count() << endl;
        outputFile.close();
    }
}

void runRandomizedExperiment(int from, int to, int experimentNumber) {
    for (int i = from; i <= to; i += 5) {
        string filename = gridsBaseDir + to_string(i) + ".bin";
        Grid grid = loadGrid(filename);
        cout << "Grid size: " << i << endl;

        auto start = chrono::high_resolution_clock::now();
        float d = closestPairRandomized(grid);
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(end - start);

        cout << "Randomized: " << duration.count() << " microseconds" << endl;

        string outputFilename = "data/results/randomized/n_" + to_string(i) +
                                "exp_" + to_string(experimentNumber) + ".csv";
        ofstream outputFile(outputFilename, ios::out | ios::app);
        outputFile << i << "," << duration.count() << endl;
        outputFile.close();
    }
}

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

    // for (int i = 1; i <= 100; i++) {
    //     cout << "Experiment #" << i << endl;
    //     runRandomizedExperiment(5, 50, i);
    // }

    // cout << grid << endl;

    // for (int i = 1; i <= 100; i++) {
    //     cout << "Experiment #" << i << endl;
    //     runDeterministicExperiment(5, 50, i);
    // }

    runRandomizedExperiment(5, 50, 1);

    return 0;
}
