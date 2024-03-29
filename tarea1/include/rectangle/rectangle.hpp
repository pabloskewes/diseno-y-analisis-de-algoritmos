#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <vector>
#include <string>

using namespace std;

/**
 * @struct Point
 * @brief A struct representing a point in a 2D plane with x and y coordinates.
 */
struct Point {
    double x;
    double y;
};

/**
 * @struct Rectangle
 * @brief A struct representing a rectangle with a bottom left and top right
 * point.
 */
struct Rectangle {
    Point bottom_left;
    Point top_right;
};

void print_rectangle(Rectangle rect);
Point middle_point(Rectangle rect);
double rectangle_area(Rectangle rect);
bool intersects(Rectangle rect1, Rectangle rect2);
Rectangle computeMBR(vector<Rectangle> rectangles);
void write_rectangles_to_file(std::vector<Rectangle> rects, string filename);
std::vector<Rectangle> read_rectangles_from_file(string filename);

#endif // RECTANGLE_HPP
