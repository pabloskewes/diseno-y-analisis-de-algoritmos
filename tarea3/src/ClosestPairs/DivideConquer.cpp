#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <bits/stdc++.h>
#include "../../include/Grid/Grid.hpp"
#include "../../include/Grid/bulkGeneration.hpp"
#include "../../src/Grid/Grid.cpp"




using namespace std;

bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

float euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(vector<Point>& points, int left, int right) {
    float minDistance = numeric_limits<float>::infinity();
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            minDistance = min(minDistance, euclideanDistance(points[i], points[j]));
        }
    }
    return minDistance;
}

float closestPairUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        return bruteForce(points, left, right);
    }

    int mid = (left + right) / 2;
    float leftMin = closestPairUtil(points, left, mid);
    float rightMin = closestPairUtil(points, mid, right);
    float minDistance = min(leftMin, rightMin);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - points[mid].x) < minDistance) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDistance; ++j) {
            minDistance = min(minDistance, euclideanDistance(strip[i], strip[j]));
        }
    }

    return minDistance;
}

float closestPair(Grid& grid) {
    sort(grid.points.begin(), grid.points.end(), compareX);
    return closestPairUtil(grid.points, 0, grid.points.size());
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
            float dis = euclideanDistance(grid.points[i], grid.points[j]);
            if (d > dis)
                d = dis;
        }
    }
    return d;
}


int main() {
    cout << "Hello, World!" << endl;


    Grid grid = generateGrid(1000000);

    float mindistance = closestPair(grid);
    cout << "The closest pair of points in the grid is: " << mindistance << endl;
    float mindistance2 = closestPairForced(grid);

    //print each distance
    cout << "The closest pair of points in the grid is: " << mindistance2 << endl;


}