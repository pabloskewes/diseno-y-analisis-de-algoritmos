#include "Grid/bulkGeneration.hpp"
#include "Grid/Grid.hpp"
#include <cmath>
#include <string>

using namespace std;

/**
 * @brief Generates grids with n points on a [0, 1] x [0, 1] grid. The grids are
 * written to files with the given filenames in binary.
 * @param n_start The number of points to start with.
 * @param n_end The number of points to end with.
 * @param n_step The number of points to increment with.
 * @param baseFilename The base filename to write to.
 */
void bulkGenerateGrids(int n_start, int n_end, int n_step,
                       string baseFilename) {
    int divisionFactor = pow(10, 6);
    for (int n = n_start; n <= n_end; n += n_step) {
        string filename = baseFilename + to_string(n / divisionFactor) + ".bin";
        Grid generatedGrid = generateGrid(n);
        writeGrid(generatedGrid, filename);
    }
}

/**
 * @brief Generates grids with n points on a [0, 1] x [0, 1] grid. The grids are
 * written to files with the given filenames in binary.
 * @param baseFilename The base filename to write to.
 */
void bulkGenerateGrids(string baseFilename) {
    int n_start = 5 * pow(10, 6);
    int n_end = 50 * pow(10, 6);
    int n_step = 5 * pow(10, 6);
    bulkGenerateGrids(n_start, n_end, n_step, baseFilename);
}
