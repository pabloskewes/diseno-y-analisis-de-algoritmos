#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Computes the number of bits of a number
 * @param num The number to compute the number of bits
 * @return The number of bits of the number
 */
int numBits(unsigned long long num) {
    return (int)log2(num) + 1;
}

/**
 * @brief Extracts the bits from a number
 * @param num The number to extract the bits from
 * @param k The number of bits to extract
 * @param mask The mask to apply to the number
 * @param iteration The iteration of the radix sort
 * @return The extracted bits
 */
unsigned long long extractBits(unsigned long long num, int k,
                               unsigned long long mask, int iteration) {

    unsigned long long indexMask = num & mask;
    unsigned long long bucketIndex = indexMask >> (iteration * k);

    return bucketIndex;
}

/**
 * @brief Sorts an array using the bucket sort algorithm
 * @param arr The array to sort
 * @param k The number of bits to sort at a time
 * @param iteration The iteration of the radix sort
 */
void bucketSort(vector<unsigned long long> &arr, int k, int iteration) {
    unsigned long long mask = (1ULL << k * (iteration + 1)) - 1;

    vector<vector<unsigned long long>> buckets(1 << k);

    for (unsigned long long &num : arr) {
        unsigned long long bucketIndex = extractBits(num, k, mask, iteration);

        buckets[bucketIndex].push_back(num);
    }

    arr.clear();

    for (int i = 0; i < (1 << k); i++) {
        for (unsigned long long num : buckets[i]) {
            arr.push_back(num);
        }
    }
}

/**
 * @brief Sorts an array using the radix sort algorithm
 * @param arr The array to sort
 * @param numBits The number of bits to sort at a time
 * @param maxBits The maximum number of bits of the numbers
 */
void radixSort(vector<unsigned long long> &arr, int k, int maxBits) {
    for (int i = 0; i < (maxBits / k); i++) {
        // cout << "Iteration: " << i << endl;
        // cout << "From: " << i * k << " to: " << (i + 1) * k << endl;
        // cout << "arr before: ";
        // for (unsigned long long num : arr) {
        //     cout << num << " ";
        // }
        bucketSort(arr, k, i);
    }
}

/**
 * @brief Sorts an array using the radix sort algorithm
 * @param arr The array to sort
 * @param k The number of bits to sort at a time
 */
void radixSort(vector<unsigned long long> &arr, int k) {
    unsigned long long maxValue = *max_element(arr.begin(), arr.end());
    int bits = numBits(maxValue);
    cout << "Number of bits: " << bits << endl;
    radixSort(arr, k, bits);
}

// int main() {
//     // Define the vector with your data
//     // vector<unsigned long long> numbers = {0b1001010, 0b1101010, 0b11111010,
//     //                                       0b1101100, 0b100100, 0b1011110,
//     //                                       0b1000010, 0b1100101};
//     vector<unsigned long long> numbers = {
//         928374, 123456,    123456789,       1234567891234,   1234567,        1,
//         2,      987654321, 987654321987654, 987654321987655, 987654331987654};

//     // Set the number of bits to sort at a time
//     int k = 16;
//     int maxBits = 64;

//     // Perform radix sort with the specified number of bits
//     radixSort(numbers, k, maxBits);
//     cout << "arr after: ";

//     // Print the sorted vector
//     for (unsigned long long num : numbers) {
//         cout << num << " ";
//     }

//     return 0;
// }