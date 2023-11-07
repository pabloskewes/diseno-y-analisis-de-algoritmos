#include <vector>
#include <algorithm>

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

/**
 * @brief Check if 2 arrays have the same elements (even in different order)
 * @param arr1
 * @param arr2
 * @return bool
 */
bool hasSameElements(std::vector<unsigned long long> &arr1,
                     std::vector<unsigned long long> &arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());

    return std::equal(arr1.begin(), arr1.end(), arr2.begin());
}
