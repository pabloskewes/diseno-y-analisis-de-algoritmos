#ifndef HASHING_HPP
#define HASHING_HPP

#include "Hashing/LinkedList.hpp"
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
    Hashing() : gen(rd()) {
        size = 0;
        m = 100000;
        p = 1000000009;
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
    T& get(int key) {
        long long index = hash(key);
        return buckets[index].get(key);
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