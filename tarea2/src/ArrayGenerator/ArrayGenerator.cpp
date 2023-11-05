#include "libs/progressbar.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

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
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<unsigned long long> distribution(minNumber,
                                                                   maxNumber);

    vector<unsigned long long> numbers(arraySize);

    for (int i = 0; i < arraySize; i++) {
        numbers[i] = distribution(rng);
    }

    return numbers;
}

/**
 * Saves an array of numbers to a binary file.
 * @param fileName The name of the file.
 * @param numbers The array of numbers.
 */
void saveArrayToFile(string fileName, vector<unsigned long long> numbers) {
    ofstream outFile(fileName, ios::binary);

    if (outFile.is_open()) {
        for (const auto &number : numbers) {
            outFile.write(reinterpret_cast<const char *>(&number),
                          sizeof(number));
        }
        outFile.close();
    } else {
        std::cerr << "Failed to open the output file." << std::endl;
    }
    return;
}

/**
 * Loads an array of numbers from a binary file.
 * @param fileName The name of the file.
 * @return The array of numbers.
 */
vector<unsigned long long> loadArrayFromFile(string fileName) {
    vector<unsigned long long> numbers;

    ifstream inFile(fileName, ios::binary);

    if (inFile.is_open()) {
        unsigned long long number;
        while (inFile.read(reinterpret_cast<char *>(&number), sizeof(number))) {
            numbers.push_back(number);
        }
        inFile.close();
    } else {
        std::cerr << "Failed to open the input file." << std::endl;
    }

    return numbers;
}

/**
 * Builds the name of the file that will be used to store the array.
 * @param baseName The base name of the file.
 * @param u The size of the universe.
 * @param iteration The iteration number.
 * @return The name of the file.
 */
string getArrayFileName(string baseName, int uPower, int iteration) {
    return baseName + "u" + to_string(uPower) + "_arr" + to_string(iteration) +
           ".bin";
}

void generateArrayTest() {
    unsigned long long N = pow(10, 8);
    int MAX_U = 64;
    string baseName = "data/arrays/";
    cout << "Generating test array..." << endl;

    vector<unsigned long long> numbers =
        generateRandomArray(N, 0, pow(2, MAX_U) - 1);
    string fileName = baseName + "test.bin";
    saveArrayToFile(fileName, numbers);
    cout << "Generated " << numbers.size() << " numbers and saved them to "
         << fileName << endl;

    vector<unsigned long long> numbers2 = loadArrayFromFile(fileName);
    cout << "Loaded " << numbers2.size() << " numbers from " << fileName
         << endl;

    // checking if the numbers are the same
    bool areEqual = true;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] != numbers2[i]) {
            areEqual = false;
            break;
        }
    }
    if (areEqual) {
        cout << "The numbers are the same." << endl;
    } else {
        cout << "The numbers are not the same." << endl;
    }
}

void generateArrays() {
    unsigned long long N = pow(10, 8);
    int MIN_U = 1;
    int MAX_U = 64;
    int ITERATIONS = 100;
    string baseName = "data/arrays/";
    cout << "Generating arrays..." << endl;

    progressbar bar(ITERATIONS * (MAX_U - MIN_U + 1));
    for (int uPower = MIN_U; uPower <= MAX_U; uPower++) {
        unsigned long long u;
        if (uPower == 64) {
            u = pow(2, uPower) - 1;
        } else {
            u = pow(2, uPower);
        }
        for (int iteration = 0; iteration < ITERATIONS; iteration++) {
            vector<unsigned long long> numbers = generateRandomArray(N, 1, u);
            string fileName = getArrayFileName(baseName, uPower, iteration);
            saveArrayToFile(fileName, numbers);
            bar.update();
        }
    }
}