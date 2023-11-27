#include <bits/stdc++.h>
#include "Grid.hpp"



using namespace std;
// Function to calculate the square of the Euclidean distance between two points
float distanceSquare(const Point& p1, const Point& p2) {
    return (float)(p1.x - p2.x) * (p1.x - p2.x) + (float)(p1.y - p2.y) * (p1.y - p2.y);
}

/*
    * Function to find the closest pair of points in the set of points
    * represented as a vector of points
    * @param grid A Grid struct representing a grid with a set of points and a set of edges.
    * @return The smallest distance between two points in the grid.
*/

// To find the closest pair of points
float closestPair(const Grid& grid) {
    int n = grid.points.size();

    // Vector pair to store points on plane
    vector<Point> v = grid.points;

    // Sort them according to their x-coordinates
    sort(v.begin(), v.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    // Minimum distance b/w points seen so far
    float d = LONG_MAX;

    // Keeping the points in increasing order
    set<Point> st;
    st.insert({v[0].x, v[0].y});

    for (int i = 1; i < n; i++) {
        auto l = st.lower_bound({v[i].x - d, v[i].y - d});
        auto r = st.upper_bound({v[i].x, v[i].y + d});
        if (l == st.end())
            continue;

        for (auto p = l; p != r; p++) {
            Point val = *p;
            float dis = distanceSquare(v[i], val);

            // Updating the minimum distance dis
            if (d > dis)
                d = dis;
        }
        st.insert({v[i].x, v[i].y});
    }

    return d;
}

/*
* Forcated form of finding the closest pair of points in the set of points, by comparing every point distance
* @param grid A Grid struct representing a grid with a set of points and a set of edges.
* @return The smallest distance between two points in the grid.
*/
float closestPairForced(const Grid& grid) {
    int n = grid.points.size();
    float d = LONG_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n ; j++) {
            float dis = distanceSquare(grid.points[i], grid.points[j]);
            if (d > dis)
                d = dis;
        }
    }
    return d;
}


// Driver code
int main() {

    // Points on a plane P[i] = {x, y}
    Grid grid;
    grid.points = {
        {1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {5.0, 6.0}, {2.0, 1.0}
    };

    // Function call
    cout << "The smallest distance is " << closestPair(grid);
    return 0;
}