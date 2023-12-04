#ifndef HASHING_HPP
#define HASHING_HPP

#include "Hashing/LinkedList.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

/**
 * @brief      Hashing data structure for storing data as follows:
 *            - Each bucket is a linked list.
 *            - Each bucket is indexed by a hash function.
 *            - Keys can only be integers and values can be any type (T).
 *            - The hash function is a simple modulo function: takes an x and
 * computes ((ax+b) mod p) mod m, where a and b are randomly chosen between [1,
 * ...p-1] and [0, ..., p-1], p is a big prime number and m will be fixed.
 *
 * @tparam     T     Type of data to store in the list.
 */
template <typename T> struct Hashing {

    vector<LinkedList<T>> buckets;
    int size;
    long long m;
    long long a;
    long long b;
    long long p;

    random_device rd;
    mt19937 gen;

    /**
     * @brief      Constructs the object.
     */
    Hashing(long long m) {
        gen = mt19937(rd());
        size = 0;
        p = 1000000007;
        this->m = m;
        a = uniform_int_distribution<long long>(1, p - 1)(gen);
        b = uniform_int_distribution<long long>(0, p - 1)(gen);
        buckets.resize(m);
    }

    /**
     * @brief      Inserts a key-value pair into the hash table.
     *
     * @param[in]  key    The key
     * @param[in]  value  The value
     */
    void insert(int key, const T &value) {
        long long index = hash(key);
        buckets[index].push_back(value, key);
    }

    /**
     * @brief      Gets the first value associated with the given key.
     *
     * @param[in]  key   The key
     *
     * @return     A reference to the value associated with the given key.
     */
    T &get(int key) {
        long long index = hash(key);
        return buckets[index].get(key);
    }

    /**
     * @brief      Returns true if the given key is in the hash table.
     * @param[in]  key   The key
     * @return     True if the given key is in the hash table, False otherwise.
     */
    bool contains(int key) {
        long long index = hash(key);
        return !buckets[index].empty();
    }

    /**
     * @brief      Prints the hash table.
     */
    void print() {
        for (int i = 0; i < m; i++) {
            if (buckets[i].empty()) {
                continue;
            }
            cout << i << ": ";
            buckets[i].print();
        }
    }

    /**
     * @brief      Prints the hash table.
     */
    void printStats() {
        cout << "m = " << m << endl;
        cout << "p = " << p << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

    /**
     * @brief      Gets the value counts in the hash table.
     * @return     The value counts.
     */
    vector<int> getValueCounts() {
        vector<int> valueCounts;
        for (int i = 0; i < m; i++) {
            if (buckets[i].empty()) {
                continue;
            }
            valueCounts.push_back(buckets[i].size);
        }
        return valueCounts;
    }

    /**
     * @brief      Gets stats on the value counts in the hash table:
     *             count, min, max, mean, median, quartiles, etc.
     * @return     The value counts stats.
     */
    vector<float> getValueCountsStats() {
        vector<int> valueCounts = getValueCounts();
        vector<float> valueCountsStats;
        int n = valueCounts.size();
        if (n == 0) {
            return valueCountsStats;
        }
        sort(valueCounts.begin(), valueCounts.end());
        valueCountsStats.push_back(n);
        valueCountsStats.push_back(valueCounts[0]);
        valueCountsStats.push_back(valueCounts[n - 1]);
        float sum = 0;
        for (int i = 0; i < n; i++) {
            sum += valueCounts[i];
        }
        valueCountsStats.push_back(sum / n);
        valueCountsStats.push_back(valueCounts[n / 2]);
        valueCountsStats.push_back(valueCounts[n / 4]);
        valueCountsStats.push_back(valueCounts[3 * n / 4]);
        return valueCountsStats;
    }

    void printValueCountsStats() {
        vector<float> valueCountsStats = getValueCountsStats();
        int n = valueCountsStats.size();
        if (n == 0) {
            return;
        }
        cout << "Value counts stats:" << endl;
        cout << "size: " << valueCountsStats[0] << endl;
        cout << "mean: " << valueCountsStats[3] << endl;
        cout << "min: " << valueCountsStats[1] << endl;
        cout << "first quartile: " << valueCountsStats[5] << endl;
        cout << "median: " << valueCountsStats[4] << endl;
        cout << "third quartile: " << valueCountsStats[6] << endl;
        cout << "max: " << valueCountsStats[2] << endl;
    }

    /**
     * @brief      Gets the perteage of buckets that are empty.
     * @return     The percentage of empty buckets.
     */
    float getPercentageOfEmptyBuckets() {
        int emptyBuckets = 0;
        for (int i = 0; i < m; i++) {
            if (buckets[i].empty()) {
                emptyBuckets++;
            }
        }
        return (float)emptyBuckets / m;
    }

  private:
    /**
     * @brief      Hash function.
     * @param[in]  x     The value to hash.
     * @return     Hashed value.
     */
    long long hash(int x) {
        return ((a * x + b) % p) % m;
    }
};

#endif // HASHING_HPP