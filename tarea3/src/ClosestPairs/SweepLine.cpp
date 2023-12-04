#include "ClosestPairs/BruteForce.hpp"
#include "Grid/Grid.hpp"
#include <bits/stdc++.h>
#include <tuple>

using namespace std;

/**
 * @brief Compute the distance between two points using the Sweepline algorithm
 *
 * @param coordinates Vector of points
 * @param n Number of points
 * @return long Distance between the closest pair of points
 */
tuple<Point, Point, float> closestPair(vector<Point> &coordinates, int n) {
    int i;
    // Vector pair to store points on plane
    vector<Point> v;
    for (i = 0; i < n; i++)
        v.push_back({coordinates[i].x, coordinates[i].y});

    // Sort them according to their
    // x-coordinates
    sort(v.begin(), v.end(), [](Point &a, Point &b) { return a.x < b.x; });

    // Minimum distance b/w points
    // seen so far
    float d = numeric_limits<float>::infinity();
    Point p1, p2;

    // Keeping the points in
    // increasing order
    set<Point> st;
    st.insert({v[0].x, v[0].y});

    for (i = 1; i < n; i++) {
        auto l = st.lower_bound({v[i].x - d, v[i].y - d});
        auto r = st.upper_bound({v[i].x, v[i].y + d});
        if (l == st.end())
            continue;

        for (auto p = l; p != r; p++) {
            Point val = *p;
            float dis = euclideanDistance(val, v[i]);

            // Updating the minimum
            // distance dis
            if (d > dis) {
                d = dis;
                p1 = val;
                p2 = v[i];
            }
        }

        // Inserting points in set
        st.insert({v[i].x, v[i].y});
    }

    return make_tuple(p1, p2, d);
}

/**
 * @brief Compute the distance between two points using the Sweepline algorithm
 *
 * @param coordinates Vector of points
 * @return tuple<Point, Point, float> Tuple containing the closest pair of
 * points and the distance between them
 */
tuple<Point, Point, float> closestPairSweepLine(vector<Point> &coordinates) {
    int n = coordinates.size();
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++)
        v.push_back({coordinates[i].x, coordinates[i].y});

    return closestPair(coordinates, n);
}

/**
 * @brief Compute the distance between two points using the Sweepline algorithm
 *
 * @param grid Grid of points
 * @return tuple<Point, Point, float> Tuple containing the closest pair of
 * points and the distance between them
 */
tuple<Point, Point, float> closestPairSweepLine(Grid grid) {
    return closestPairSweepLine(grid.points);
}