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


bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

float dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float findClosestPoints(const Grid& grid) {
    int n = grid.points.size();

    if (n < 2) {
        // No hay suficientes puntos para calcular la distancia mínima.
        cerr << "Error: Menos de dos puntos en la cuadrícula." << endl;
        exit(1);
    }

    // Ordenar los puntos por su coordenada x.
    vector<Point> sortedPoints = grid.points;
    sort(sortedPoints.begin(), sortedPoints.end(), compareX);

    float minDistance = numeric_limits<float>::max();
    pair<Point, Point> closestPoints;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Verificar si la distancia entre los puntos actuales es menor que la mínima conocida.
            float currentDistance = dist(sortedPoints[i], sortedPoints[j]);
            if (currentDistance < minDistance) {
                minDistance = currentDistance;
                closestPoints = make_pair(sortedPoints[i], sortedPoints[j]);
            }
        }
    }

    return minDistance;
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
            float dis = dist(grid.points[i], grid.points[j]);
            if (d > dis)
                d = dis;
        }
    }
    return d;
}


int main() {
    cout << "Hello, World!" << endl;


    Grid grid = generateGrid(100000);

    float mindistance = findClosestPoints(grid);
    cout << "The closest pair of points in the grid is: " << mindistance << endl;
    float mindistance2 = closestPairForced(grid);

    //print each distance
    cout << "The closest pair of points in the grid is: " << mindistance2 << endl;


}