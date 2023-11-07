#include <iostream>
#include <random>
#include <vector>

std::random_device rd_qs;
std::mt19937 gen(rd_qs());
std::uniform_int_distribution<int> dist;

/**
 * @brief Choose a random pivot between low and high
 * @param low
 * @param high
 * @return * Function
 */
int chooseRandomPivot(int low, int high) {
    dist.param(std::uniform_int_distribution<int>::param_type(low, high));
    return dist(gen);
}

/**
 * @brief Partition the array around a pivot
 * @param arr
 * @param low
 * @param high
 * @return int
 */
int partition(std::vector<unsigned long long> &arr, int low, int high) {
    int pivotIndex = chooseRandomPivot(low, high);
    unsigned long long pivotValue = arr[pivotIndex];

    // Move the pivot to the end
    std::swap(arr[pivotIndex], arr[high]);

    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivotValue) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }

    // Move the pivot back to its correct position
    std::swap(arr[i], arr[high]);
    return i;
}

/**
 * @brief Quicksort algorithm using random pivot
 * @param arr
 * @param low
 * @param high
 */
void quickSort(std::vector<unsigned long long> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

/**
 * @brief Quicksort algorithm using random pivot
 * @param arr
 */
void quickSort(std::vector<unsigned long long> &arr) {
    quickSort(arr, 0, arr.size() - 1);
}