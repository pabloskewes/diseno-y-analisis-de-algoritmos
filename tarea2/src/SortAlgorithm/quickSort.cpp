#include <iostream>
#include <vector>
#include <random>

/**
 * @brief Choose a random pivot between low and high
 * @param low 
 * @param high 
 * @return * Function 
 */


int chooseRandomPivot(int low, int high) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
}

/**
 * @brief Partition the array around a pivot
 * @param arr 
 * @param low 
 * @param high 
 * @return int 
 */

int partition(std::vector<unsigned long long>& arr, int low, int high) {
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
  * @brief Quicksort function
  * 
  * @param arr 
  * @param low 
  * @param high 
  */

void quickSort(std::vector<unsigned long long>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}