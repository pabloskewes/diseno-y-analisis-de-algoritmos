#include <Array/ArrayGenerator.hpp>
#include <Array/isSorted.hpp>
#include <SortAlgorithm/quickSort.hpp>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << "Hello world!" << endl;

    // int arraySize = 100;
    int arraySize = pow(10, 8);
    int universePower = 64;
    vector<unsigned long long> numbers = generateRandomArray(arraySize, universePower); 

    cout << "Array size: " << numbers.size() << endl;
    cout << "Universe power: " << universePower << endl;

    quickSort(numbers);

    cout << "Is sorted: " << isSorted(numbers) << endl;

    return 0;
}
