#include "Grid/Grid.hpp"
#include "Grid/bulkGeneration.hpp"
#include <iostream>

using namespace std;

string gridsBaseDir = "data/grids/";

int main() {
    cout << "Hello, World!" << endl;

    // Generate grids
    // bulkGenerateGrids(gridsBaseDir);

    // Load grid
    for (int i = 5; i <= 50; i += 5) {
        string filename = gridsBaseDir + to_string(i) + ".bin";
        Grid grid = loadGrid(filename);
        printGrid(grid);
    }


}
