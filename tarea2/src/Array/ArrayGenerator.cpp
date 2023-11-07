#include "libs/progressbar.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

std::random_device rd;
std::mt19937_64 rng(rd());

/**
 * Generates a random array of numbers and saves it to a file.
 * @param arraySize The size of the array.
 * @param minNumber The minimum number that can be generated.
 * @param maxNumber The maximum number that can be generated.
 * @return The generated array.
 */
vector<unsigned long long> generateRandomArray(int arraySize,
                                               unsigned long long minNumber,
                                               unsigned long long maxNumber) {

    std::uniform_int_distribution<unsigned long long> distribution(minNumber,
                                                                   maxNumber);

    vector<unsigned long long> numbers(arraySize);

    for (int i = 0; i < arraySize; i++) {
        numbers[i] = distribution(rng);
    }

    return numbers;
}

/**
 * Generates a random array of numbers and saves it to a file.
 * @param arraySize The size of the array.
 * @param universePower The power of the universe.
 * @return The generated array.
 */
vector<unsigned long long>
generateRandomArray(int arraySize, int universePower) {
    if (universePower > 64) {
        throw "Universe power must be less than 64";
    }
    if (universePower == 64) {
        return generateRandomArray(arraySize, 1, pow(2, universePower) - 1);
    }
    return generateRandomArray(arraySize, 1, pow(2, universePower));
}