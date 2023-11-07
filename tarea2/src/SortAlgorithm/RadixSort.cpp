#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Get the Max object
 * @param numbers
 * @return unsigned long long
 *  */
unsigned long long getMax(vector<unsigned long long> &numbers) {
    return *max_element(numbers.begin(), numbers.end());
}

/**
 * @brief Extract the digits from a number, from right to left
 * @param number The number to extract the digits from
 * @param first The position of the first digit to extract
 * @param last The position of the last digit to extract
 * @return int
 * */
int extractDigits(unsigned long long n, int first, int last) {
    return (n / static_cast<unsigned long long>(pow(10, first))) %
           static_cast<unsigned long long>(pow(10, last - first + 1));
}

/**
 * @brief Counting sort algorithm
 * @param arr The array to be sorted
 * @param group The group of digits to be sorted
 * @param k The number of digits to use on each round
 * */
void countingSort(vector<unsigned long long> &arr, int first, int last) {
    int n = arr.size();
    vector<unsigned long long> output(n);
    int universeSize = pow(10, last - first + 1);
    vector<int> count(universeSize, 0);

    for (int i = 0; i < n; i++) {
        count[extractDigits(arr[i], first, last)]++;
    }

    for (int i = 1; i < universeSize; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[extractDigits(arr[i], first, last)] - 1] = arr[i];
        count[extractDigits(arr[i], first, last)]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

/**
 * @brief Radix sort algorithm
 * @param arr The array to be sorted
 * @param k The number of digits to use on each round
 * */
void radixSort(vector<unsigned long long> &arr, int k) {
    unsigned long long max = getMax(arr);
    int numDigits = static_cast<int>(log10(max)) + 1;

    for (int i = 0; i < numDigits; i+=k) {
        countingSort(arr, i, min(i + k - 1, numDigits - 1));
    }
}
