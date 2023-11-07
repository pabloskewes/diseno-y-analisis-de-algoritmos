#include <Array/ArrayGenerator.hpp>
#include <Array/ArrayChecker.hpp>
#include <SortAlgorithm/QuickSort.hpp>
#include <SortAlgorithm/RadixSort.hpp>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << "Hello world!" << endl;

    // int arraySize = 100;
    int arraySize = pow(10, 6);
    int universePower = 64;
    vector<unsigned long long> numbers = generateRandomArray(arraySize, universePower); 

    cout << "Array size: " << numbers.size() << endl;
    cout << "Universe power: " << universePower << endl;

    vector<unsigned long long> numbersCopy = numbers;

    // quickSort(numbers);
    radixSort(numbers, 10);

    cout << "Is sorted: " << isSorted(numbers) << endl;
    cout << "Has same elements: " << hasSameElements(numbers, numbersCopy) << endl;

    return 0;
}
