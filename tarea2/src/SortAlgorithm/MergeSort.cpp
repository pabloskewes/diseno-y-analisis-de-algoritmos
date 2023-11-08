#include <vector>

using namespace std;

/**
 * @brief Merges two sorted arrays
 * @param arr The array to merge
 * @param left The left index of the array
 * @param mid The middle index of the array
 * @param right The right index of the array
 */
void merge(vector<unsigned long long> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<unsigned long long> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Sorts an array using the merge sort algorithm
 * @param arr The array to sort
 * @param left The left index of the array
 * @param right The right index of the array
 */
void mergeSort(vector<unsigned long long> &arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/**
 * @brief Sorts an array using the merge sort algorithm
 * @param arr The array to sort
 */
void mergeSort(vector<unsigned long long> &arr) {
    mergeSort(arr, 0, arr.size() - 1);
}
