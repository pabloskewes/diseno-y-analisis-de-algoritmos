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

        string outputFilename = "data/results/HashingFunction/n_" + to_string(i) +
                                "exp_" + to_string(experimentNumber) + ".csv";
        ofstream outputFile(outputFilename, ios::out | ios::app);
        outputFile << i << "," << duration.count() << endl;
        outputFile.close();
    }
}

int main() {
    cout << "Hello, World!!!" << endl;
    
    // iteracion para crear los experimentos de los algoritmos
    // for (int i = 1; i <= 100; i++) {
    //     cout << "Experiment #" << i << endl;
    //     runRandomizedExperiment(5, 50, i);
    //     runDeterministicExperiment(5, 50, i);
    // }
    // con la funcion bulkGenerateGrids se pueden generar las grillas de prueba
    // Grid grid = loadGrid("data/grids/5.bin"); // con esta función se puede cargar una grilla desde un archivo binario

    Grid grid = generateGrid(5000); // con esta función se puede crear una grilla temporal con la cual probar los algoritmos
    float d_random = closestPairRandomized(grid);
    cout << "d_random: " << d_random << endl;


    float d_det = closestPairDivideAndConquer(grid);
    cout << "d_det: " << d_det << endl;


    return 0;
}
