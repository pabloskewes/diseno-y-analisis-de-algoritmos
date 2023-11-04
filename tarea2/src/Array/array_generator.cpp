//#include "libs/progressbar.hpp"

#include <iostream>
#include <fstream>
#include <random>

using namespace std;

void generateAndSaveRandomNumbers(string fileName, int arraySize, unsigned long long minNumber, unsigned long long maxNumber) {
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<unsigned long long> distribution(minNumber, maxNumber);

    unsigned long long* numbers = new unsigned long long[arraySize];

    for (int i = 0; i < arraySize; i++) {
        numbers[i] = distribution(rng);
    }
    // prinout size of numbers
    std::cout << "Size of numbers: " << sizeof(numbers) << std::endl;
    // prinout name of file
    std::cout << "Name of file: " << fileName << std::endl;

    // Open a file for writing
    ofstream outFile;
    outFile.open(fileName);

    if (outFile.is_open()) {
        for (int i = 0; i < arraySize; i++) {
            outFile << numbers[i] << endl;
        }
        outFile.close();
        std::cout << "Random numbers have been saved to " << fileName << std::endl;
    } else {
        std::cerr << "Failed to open the output file." << std::endl;
    }

    delete[] numbers;
}

int main() {
    const int arraySize = 10;

    // i want ti iterate in the range [1, 2^64] and save the numbers in a file
    for (int u = 0; u < 64; u++) {
        unsigned long long minNumber = 1; //1
        unsigned long long maxNumber = 1 << u; //2^u

        for (int i = 0; i < 5; i++) {
            string fileName = "../../data/arrays/u_" + to_string(u) + "_array_" + to_string(i) + ".txt";
            generateAndSaveRandomNumbers(fileName, arraySize, minNumber, maxNumber);
        }
    }

    return 0;
}
