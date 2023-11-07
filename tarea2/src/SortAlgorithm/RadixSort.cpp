#include <iostream>
#include <vector>

using namespace std;

/**
 * Sorts an array of unsigned long long integers using bucket sort.
 * @param arr The array to be sorted
 * @param group The group of bits to be sorted
 * @param k The number of bits per group
 */
void bucketSort(vector<unsigned long long> &arr, int group, int k) {
    int NUM_BUCKETS = 1 << k;
    vector<unsigned long long> output(arr.size());
    vector<int> count(NUM_BUCKETS, 0);

    for (unsigned long long num : arr) {
        int digit = (num >> (group * k)) & (NUM_BUCKETS - 1);
        count[digit]++;
    }

    for (int i = 1; i < NUM_BUCKETS; i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        int digit = (arr[i] >> (group * k)) & (NUM_BUCKETS - 1);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

/**
 * Sorts an array of unsigned long long integers using radix sort.
 * @param arr The array to be sorted
 * @param k The number of bits per group
 */
void radixSort(vector<unsigned long long> &arr, int k) {
    int NUM_GROUPS = sizeof(unsigned long long) * 8 / k;

    for (int group = 0; group < NUM_GROUPS; group++) {
        bucketSort(arr, group, k);
    }
}
