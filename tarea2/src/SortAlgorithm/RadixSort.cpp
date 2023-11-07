#include <algorithm>
#include <vector>

using namespace std;

/**
 * @brief Bucket sort algorithm: sort the array in ascending order
 * @param arr: the array to be sorted
 * @param exp: the current digit
 * @param k: the number of bits of the current digit
 * @return void
 */
void bucketSort(vector<unsigned long long> &arr, unsigned long long exp,
                unsigned long long k) {
    unsigned long long mask = (1 << k) - 1;
    vector<unsigned long long> output(arr.size());
    vector<int> count(mask + 1);

    for (unsigned long long num : arr) {
        unsigned long long index = (num / exp) & mask;
        count[index]++;
    }

    for (unsigned long long i = 1; i <= mask; i++) {
        count[i] += count[i - 1];
    }

    for (long long i = arr.size() - 1; i >= 0; i--) {
        unsigned long long index = (arr[i] / exp) & mask;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    arr = output;
}

/**
 * @brief Radix sort algorithm: sort the array in ascending order
 * @param arr: the array to be sorted
 * @param k: the number of bits of the current digit
 * @return void
 */
void radixsort(vector<unsigned long long> &arr, unsigned long long k) {
    unsigned long long max = *max_element(arr.begin(), arr.end());
    for (unsigned long long exp = 1; max / exp > 0; exp <<= k) {
        bucketSort(arr, exp, k);
    }
}
