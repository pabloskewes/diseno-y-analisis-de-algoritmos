#include "rectangle/rectangle.hpp"
#include "libs/progressbar.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

/**
 * Prints a rectangle to stdout.
 * @param rect The rectangle to print.
 */
void print_rectangle(Rectangle rect) {
    cout << "Rectangle(bottom_left=(" << rect.bottom_left.x << ", "
         << rect.bottom_left.y << "), top_right=(" << rect.top_right.x << ", "
         << rect.top_right.y << "))" << endl;
}

/**
 * Calculates the middle point of a rectangle.
 * @param rect The rectangle to calculate the middle point from.
 * @return The middle point of the rectangle.
 */
Point middle_point(Rectangle rect) {
    Point middle;
    middle.x = (rect.bottom_left.x + rect.top_right.x) / 2;
    middle.y = (rect.bottom_left.y + rect.top_right.y) / 2;
    return middle;
}

/**
 * Calculates the area of a rectangle.
 * @param rect The rectangle to calculate the area from.
 * @return The area of the rectangle.
 */
double rectangle_area(Rectangle rect) {
    return (rect.top_right.x - rect.bottom_left.x) *
           (rect.top_right.y - rect.bottom_left.y);
}

/**
 * Indicates whether 2 rectangles have no non-zero area overlap.
 * @param rect1 The first rectangle.
 * @param rect2 The second rectangle.
 * @return True if the rectangles have no non-zero area overlap, false
 * otherwise.
 */
bool intersects(Rectangle rect1, Rectangle rect2) {
    return !(rect1.top_right.x < rect2.bottom_left.x ||
             rect1.bottom_left.x > rect2.top_right.x ||
             rect1.top_right.y < rect2.bottom_left.y ||
             rect1.bottom_left.y > rect2.top_right.y);
}

/**
 * Generates a random double between the specified bounds.
 * @param rectangles The vector of rectangles to compute the MBR from.
 * @return The MBR of the rectangles.
 */
Rectangle computeMBR(vector<Rectangle> rectangles) {
    double min_x = rectangles[0].bottom_left.x;
    double min_y = rectangles[0].bottom_left.y;
    double max_x = rectangles[0].top_right.x;
    double max_y = rectangles[0].top_right.y;
    for (int i = 1; i < rectangles.size(); i++) {
        if (rectangles[i].bottom_left.x < min_x)
            min_x = rectangles[i].bottom_left.x;
        if (rectangles[i].bottom_left.y < min_y)
            min_y = rectangles[i].bottom_left.y;
        if (rectangles[i].top_right.x > max_x)
            max_x = rectangles[i].top_right.x;
        if (rectangles[i].top_right.y > max_y)
            max_y = rectangles[i].top_right.y;
    }
    Rectangle MBR = {{min_x, min_y}, {max_x, max_y}};
    return MBR;
}

/**
 * Writes a vector of rectangles to a file.
 * @param rects The vector of rectangles to write to a file.
 * @param filename The name of the file to write to.
 */
void write_rectangles_to_file(vector<Rectangle> rects, string filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < rects.size(); i++) {
        file << rects[i].bottom_left.x << " " << rects[i].bottom_left.y << " "
             << rects[i].top_right.x << " " << rects[i].top_right.y << endl;
    }
    file.close();
}

/**
 * Reads a vector of rectangles from a file.
 * @param filename The name of the file to read from.
 * @return A vector of rectangles read from the file.
 */
vector<Rectangle> read_rectangles_from_file(string filename) {
    vector<Rectangle> rects;
    ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        Rectangle rect;
        sscanf(line.c_str(), "%lf %lf %lf %lf", &rect.bottom_left.x,
               &rect.bottom_left.y, &rect.top_right.x, &rect.top_right.y);
        rects.push_back(rect);
    }
    file.close();

    return rects;
}
