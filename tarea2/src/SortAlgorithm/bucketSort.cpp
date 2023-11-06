#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * Sorts an array of binary number using the bucket sort algorithm.
 * @param binList The array of bin.
 * @param arraySize The size of the array.
 * @param k number of bits of the binary numbers. (2^k will be the biggest bin number)
 * @return The sorted array.
 */

void bucketSort(std::vector<unsigned long long> &binList, int arraySize, int k) {

    int maxNumber = pow(2, k);
    std::vector<unsigned long long> buckets(maxNumber);

    // Initialize the buckets
    for (int i = 0; i < arraySize; i++) {
        // put a pointer of binList[i] in the bucket position binList[i] // falt aponer el puntero que no se como aun 
        buckets[binList[i]]++;

    }
    // Sort the buckets
    int index = 0;

    // Iterate over the buckets
    for (int i = 0; i < buckets.size(); i++) {
        
        // Iterate over the elements of each bucket
        for (int j = 0; j < buckets[i]; j++) {
            binList[index] = i;
            index++;
        }
    }
}


/**
 * Given a vector unsigned long long of bin numbers, it will go k bits by k and sort them by sending them to the bucket sort algorithm.
 * @param binList The array of bin.
 * @param arraySize The size of the array.
 * @param k number of bits it will sort
 * @param U size of the maximun bin number
 * @return The sorted array.
 */

void radixSort(std::vector<unsigned long long> &binList, int arraySize, int k, int U) {
    // Calculate the number of iterations required based on k and U
    int numIterations = std::ceil(static_cast<double>(U) / k);
    
    // Perform radix sort iteratively
    for (int i = 0; i < numIterations; i++) {
        // Extract k bits from the numbers for sorting
        for (int j = 0; j < arraySize; j++) {
            binList[j] = (binList[j] >> (i * k)) & ((1ULL << k) - 1);
        }
        
        // Use bucket sort to sort the array
        bucketSort(binList, k);
    }
    
}



// [11100,
//  10011,
//  10110]

// [0
//  1
//  2 --> 1
//  3 --> 1
// ]

// [
//  11100,
//  10110,
//  10011
//  ]
