#ifndef ARRAY_GENERATOR_HPP
#define ARRAY_GENERATOR_HPP

#include <vector>
#include <string>

using namespace std;

vector<unsigned long long> generateRandomArray(int arraySize,
                                               unsigned long long minNumber,
                                               unsigned long long maxNumber);
void saveArrayToFile(string fileName, vector<unsigned long long> numbers);
vector<unsigned long long> loadArrayFromFile(string fileName);
void generateArrays();

#endif //ARRAY_GENERATOR_HPP
