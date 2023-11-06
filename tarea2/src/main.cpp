#include <ArrayGenerator/ArrayGenerator.hpp>
#include <iostream>

using namespace std;

int main() {
    cout << "Hello world!" << endl;

    int arraySize = 100;
    int universePower = 64;
    vector<unsigned long long> numbers = generateRandomArray(arraySize, universePower); 

    for (int i = 0; i < arraySize; i++) {
        cout << numbers[i] << endl;
    }

    return 0;
}
