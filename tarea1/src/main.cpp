#include "rectangle/rect_generator.hpp"
#include "rectangle/rectangle.hpp"
#include "rectangle/test_rectangle.hpp"
#include "rtree/HilbertCurve.hpp"
#include "rtree/RTree.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

void optimize() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

void disableCache() {
    system("echo 3 | sudo tee /proc/sys/vm/drop_caches");
}

void generateInputRectagles(int power) {
    int first_power = 10;
    int last_power = 25;
    for (int i = first_power; i <= last_power; i++) {
        generate_input_samples(i);
    }
}

int calculate_M(int B, int node_size, int child_size) {
    return (B - node_size) / child_size;
}

RTree saveBtreeBin(int power, BulkLoadingAlgorithm algorithm, int M) {
    string sample_file = "data/rectangles/input_" + to_string(power) + ".txt";
    vector<Rectangle> rectangles = read_rectangles_from_file(sample_file);

    cout << "POW: " << power << endl;
    cout << "ALG: " << algorithm << endl;
    cout << "Bulk loading..." << endl;
    RTree rtree = RTree::bulkLoad(M, rectangles, algorithm);

    rtree.computeNodesOffset();

    string base_name = "data/btrees/";
    switch (algorithm) {
    case NearestX:
        base_name += "nearest_x/";
        break;
    case HilbertCurve:
        base_name += "hilbert_curve/";
        break;
    case SortTileRecursive:
        base_name += "sort_tile_recursive/";
        break;
    default:
        throw "Invalid algorithm";
    }

    cout << "Writing to disk..." << endl;
    string file_name = base_name + "pow_" + to_string(power) + ".bin";
    rtree.writeNodesToDisk(file_name);

    return rtree;
}

void createAndSaveRTrees(int M) {
    int first_power = 10;
    int last_power = 25;

    for (int i = first_power; i <= last_power; i++) {
        for (BulkLoadingAlgorithm algorithm :
             {NearestX, HilbertCurve, SortTileRecursive}) {
            saveBtreeBin(i, algorithm, M);
        }
    }
}

void runExperiment(BulkLoadingAlgorithm algorithm, int M) {
    vector<Rectangle> Q =
        read_rectangles_from_file("data/rectangles/query.txt");

    string algorithm_name;
    switch (algorithm) {
    case NearestX:
        algorithm_name = "nearest_x";
        break;
    case HilbertCurve:
        algorithm_name = "hilbert_curve";
        break;
    case SortTileRecursive:
        algorithm_name = "sort_tile_recursive";
        break;
    default:
        throw "Invalid algorithm";
    }

    cout << "Running " << algorithm_name << endl;

    string timesOutputFile = "data/results/times_" + algorithm_name + ".csv";
    string readsOutputFile = "data/results/reads_" + algorithm_name + ".csv";

    vector<vector<unsigned long long>> times;
    vector<vector<int>> reads;

    // For each 2^i
    for (int i = 10; i <= 25; i++) {
        cout << "Running for 2^" << i << endl;
        string nodesFile =
            "data/btrees/" + algorithm_name + "/pow_" + to_string(i) + ".bin";
        RTree rtree = RTree::loadFromDisk(M, nodesFile);

        vector<unsigned long long> timesForPow;
        vector<int> readsForPow;
        // For each q in Q
        for (int j = 0; j < Q.size(); j++) {
            int readCounter = 0;
            auto start = chrono::high_resolution_clock::now();

            vector<Rectangle> result = rtree.query(Q[j], &readCounter);

            auto end = chrono::high_resolution_clock::now();
            auto duration =
                chrono::duration_cast<chrono::microseconds>(end - start);
            timesForPow.push_back(duration.count());
            readsForPow.push_back(readCounter);
        }
        times.push_back(timesForPow);
        reads.push_back(readsForPow);
    }

    // Write results to file
    ofstream timesFile(timesOutputFile);
    ofstream readsFile(readsOutputFile);

    for (int i = 0; i < times.size(); i++) {
        for (int j = 0; j < times[i].size(); j++) {
            timesFile << times[i][j] << ",";
            readsFile << reads[i][j] << ",";
        }
        timesFile << endl;
        readsFile << endl;
    }

    timesFile.close();
    readsFile.close();

    cout << "Finished " << algorithm_name << endl;
}

int main() {
    optimize();

    // Computing right size for M
    int B = 4096; // 4KB: block size

    int node_size = sizeof(bool) +               // 1 byte for is_leaf
                    sizeof(unsigned long long) + // 8 bytes for offset
                    sizeof(int) +                // 4 bytes for num_rectangles
                    sizeof(int);                 // 4 bytes for num_children

    int child_size =
        sizeof(Rectangle) +
        sizeof(
            unsigned long long); // 32 bytes for rectangle, 8 bytes for offset

    int M = calculate_M(B, node_size, child_size);

    cout << "M=" << M << endl;

    for (int i = 10; i <= 25; i++) {
        saveBtreeBin(i, HilbertCurve, M);
    }

    // for (BulkLoadingAlgorithm algorithm : {
    //          SortTileRecursive,
    //          NearestX,
    //          HilbertCurve,
    //      }) {
    //     auto start = chrono::high_resolution_clock::now();
    //     runExperiment(algorithm, M);
    //     auto end = chrono::high_resolution_clock::now();
    //     auto duration =
    //         chrono::duration_cast<chrono::microseconds>(end - start);
    //     int milliseconds = duration.count() / 1000;
    //     cout << "Experiment for " << algorithm << " took " << milliseconds
    //          << "ms" << endl;
    // }

    return 0;
}
