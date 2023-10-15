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
 * @struct Rectangle
 * @brief A struct representing a rectangle with a bottom left and top right
 * point.
 */
struct Rectangle {
    Point bottom_left;
    Point top_right;
};

Point middle_point(Rectangle rect);
bool intersects(Rectangle rect1, Rectangle rect2);
std::vector<Rectangle> generate_random_rectangles(int num_rects,
                                             Point bottom_left_bound,
                                             Point top_right_bound,
                                             double min_side_length,
                                             double max_side_length);

#endif // RECTANGLE_HPP
