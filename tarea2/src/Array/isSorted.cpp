#include <vector>

/**
 * @brief Check if an array is sorted
 * @param arr
 * @return bool
 */
bool isSorted(std::vector<unsigned long long> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
