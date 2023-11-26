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
 * @brief Extracts the bits from a number given positions from
 *       the right to the left
 * @param num The number to extract the bits from
 * @param first_pos The first position to extract the bits (from the right)
 * @param last_pos The last position to extract the bits (from the right)
 * @return The extracted bits
 */

unsigned long long extractBits(unsigned long long num, int first_pos,
                               int last_pos) {
    unsigned long long mask;
    if (last_pos == 64) {
        mask = ~0; 
    } else {
        mask = (1ULL << last_pos) - 1;
    }
    return (num & mask) >> first_pos;
}

/**
 * @brief Sorts an array using the bucket sort algorithm
 * @param arr The array to sort
 * @param first_pos The first position to extract the bits (from the right)
 * @param last_pos The last position to extract the bits (from the right)
 */
void bucketSort(vector<unsigned long long> &arr, int first_pos, int last_pos) {
    int bucketSize = last_pos - first_pos;
    vector<vector<unsigned long long>> buckets(1 << bucketSize);
    for (unsigned long long &num : arr) {
        unsigned long long bucketIndex = extractBits(num, first_pos, last_pos);

        buckets[bucketIndex].push_back(num);
    }
    arr.clear();
    for (int i = 0; i < buckets.size(); i++) {
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
    for (int i = 0; i < maxBits; i += k) {
        bucketSort(arr, i, min(i + k, maxBits));
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
    radixSort(arr, k, bits);
}
