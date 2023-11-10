#include <Array/ArrayChecker.hpp>
#include <Array/ArrayGenerator.hpp>
#include <SortAlgorithm/MergeSort.hpp>
#include <SortAlgorithm/QuickSort.hpp>
#include <SortAlgorithm/RadixSort.hpp>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Writes the result of an experiment to a file
 * @param baseFileName The base file name
 * @param universePower The universe power
 * @param numExperiment The experiment number
 * @param duration The duration of the experiment
 */
void writeMergeSortExperimentResult(string baseFileName, int universePower,
                                    int numExperiment, int duration) {
    string fileName = baseFileName + "u" + to_string(universePower) + "_exp" +
                      to_string(numExperiment) + ".csv";
    ofstream file(fileName, ios::app);
    file << universePower << "," << numExperiment << "," << duration << endl;
    file.close();
}

/**
 * @brief Writes the result of an experiment to a file
 * @param baseFileName The base file name
 * @param universePower The universe power
 * @param k The number of bits to extract
 * @param numExperiment The experiment number
 * @param duration The duration of the experiment
 */
void writeRadixSortExperimentResult(string baseFileName, int universePower,
                                    int k, int numExperiment, int duration) {
    string fileName = baseFileName + "u" + to_string(universePower) + "_k" +
                      to_string(k) + "_exp" + to_string(numExperiment) + ".csv";
    ofstream file(fileName, ios::app);
    file << universePower << "," << k << "," << numExperiment << "," << duration
         << endl;
    file.close();
}

/**
 * @brief Runs an experiment with merge sort
 * @param outputPath The output path
 * @param numbers The numbers to sort
 * @param universePower The universe power
 * @param numExperiment The experiment number
 */
void runMergeSortExperiment(string outputPath,
                            vector<unsigned long long> &numbers,
                            int universePower, int numExperiment) {
    vector<unsigned long long> numbersCopy = numbers;

    auto start = chrono::high_resolution_clock::now();
    mergeSort(numbersCopy);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    if (isSorted(numbersCopy)) {
        writeMergeSortExperimentResult(outputPath, universePower, numExperiment,
                                       duration.count());
    } else {
        cout << "Merge sort failed" << endl;
        cout << "Universe power: " << universePower << endl;
    }

    numbersCopy.clear();

    return;
}

/**
 * @brief Runs an experiment with radix sort
 * @param outputPath The output path
 * @param numbers The numbers to sort
 * @param universePower The universe power
 * @param k The number of bits to extract
 * @param numExperiment The experiment number
 */
void runRadixSortExperiment(string outputPath,
                            vector<unsigned long long> &numbers,
                            int universePower, int k, int numExperiment) {
    vector<unsigned long long> numbersCopy = numbers;

    auto start = chrono::high_resolution_clock::now();
    radixSort(numbersCopy, k);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    if (isSorted(numbersCopy)) {
        writeRadixSortExperimentResult(outputPath, universePower, k,
                                       numExperiment, duration.count());
    } else {
        cout << "Radix sort failed" << endl;
        cout << "Universe power: " << universePower << endl;
        cout << "k: " << k << endl;
    }

    numbersCopy.clear();

    return;
}

int main() {
    cout << "Starting experiments" << endl;

    int arraySize = pow(10, 7);
    int maxK = 26;
    string mergeSortOutputPath = "data/mergeSortResults/";
    string radixSortOutputPath = "data/radixSortResults/";

    for (int numExperiment = 101; numExperiment <= 201; numExperiment++) {
        for (int universePower = 1; universePower <= 64; universePower++) {
            vector<unsigned long long> numbers =
                generateRandomArray(arraySize, universePower);

            runMergeSortExperiment(mergeSortOutputPath, numbers, universePower,
                                   numExperiment);

            for (int k = 1; k <= min(maxK, universePower); k++) {
                runRadixSortExperiment(radixSortOutputPath, numbers,
                                       universePower, k, numExperiment);
            }

            numbers.clear();
        }
    }

    return 0;
}
