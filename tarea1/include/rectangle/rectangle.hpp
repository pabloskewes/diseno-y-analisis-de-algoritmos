#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <vector>

/**
 * @struct Point
 * @brief A struct representing a point in a 2D plane with x and y coordinates.
 */
struct Point {
    double x;
    double y;
};

/**
 * @class Rectangle
 * @brief A class representing a rectangle in a 2D plane.
 */
class Rectangle {
  public:
    Point bottom_left;
    Point top_right;

    Rectangle(Point bottom_left, Point top_right);

    void print();
    Point middle_point();
    double area();
    bool intersects(const Rectangle &other);
};

#endif // RECTANGLE_HPP
