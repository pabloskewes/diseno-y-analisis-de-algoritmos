#include "rectangle/rectangle.hpp"
#include "libs/progressbar.hpp"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

/**
 * @class Rectangle
 * @brief A class representing a rectangle in a 2D plane.
 */
class Rectangle {
  public:
    Point bottom_left;
    Point top_right;

    Rectangle(Point bottom_left, Point top_right) {
        this->bottom_left = bottom_left;
        this->top_right = top_right;
    }

    /**
     * Prints a rectangle to stdout.
     */
    void print() {
        cout << "Rectangle(bottom_left=(" << this->bottom_left.x << ", "
             << this->bottom_left.y << "), top_right=(" << this->top_right.x
             << ", " << this->top_right.y << "))" << endl;
    }

    /**
     * Calculates the middle point of a rectangle.
     * @return The middle point of the rectangle.
     */
    Point middle_point() {
        Point middle;
        middle.x = (this->bottom_left.x + this->top_right.x) / 2;
        middle.y = (this->bottom_left.y + this->top_right.y) / 2;
        return middle;
    }

    /**
     * Calculates the area of a rectangle.
     * @return The area of the rectangle.
     */
    double area() {
        return (this->top_right.x - this->bottom_left.x) *
               (this->top_right.y - this->bottom_left.y);
    }

    /**
     * Indicates whether 2 rectangles have no non-zero area overlap.
     * @param other The rectangle to check for intersection with.
     * @return True if the rectangles have no non-zero area overlap, false
     * otherwise.
     */
    bool intersects(const Rectangle &other) {
        return !(this->top_right.x < other.bottom_left.x ||
                 this->bottom_left.x > other.top_right.x ||
                 this->top_right.y < other.bottom_left.y ||
                 this->bottom_left.y > other.top_right.y);
    }
};

/**
 * Generates a random double between the specified bounds.
 * @param lower_bound The lower bound for the random double.
 * @param upper_bound The upper bound for the random double.
 * @return A random double between the specified bounds.
 */
double random_double(double lower_bound, double upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound);
    return dis(gen);
}

/**
 * Generates a set of random rectangles, with random side lengths and random
 * positions. The rectangles are guaranteed to be within the bounds specified.
 * @param num_rects The number of rectangles to generate.
 * @param bottom_left_bound The lower bound for the bottom left point of the
 * rectangles.
 * @param top_right_bound The upper bound for the top right point of the
 * rectangles.
 * @param min_side_length The minimum side length of the rectangles.
 * @param max_side_length The maximum side length of the rectangles.
 * @return A vector of random rectangles.
 */
vector<Rectangle>
generate_random_rectangles(long long num_rects, Point bottom_left_bound,
                           Point top_right_bound, double min_side_length,
                           double max_side_length, bool show_progress_bar) {
    vector<Rectangle> rects;
    progressbar bar(num_rects);
    bar.set_done_char("█");
    for (long long i = 0; i < num_rects; i++) {
        if (show_progress_bar)
            bar.update();

        double bottom_left_x = random_double(
            bottom_left_bound.x, top_right_bound.x - max_side_length);
        double bottom_left_y = random_double(
            bottom_left_bound.y, top_right_bound.y - max_side_length);
        double top_right_x =
            bottom_left_x + random_double(min_side_length, max_side_length);
        double top_right_y =
            bottom_left_y + random_double(min_side_length, max_side_length);
        Rectangle r(Point{bottom_left_x, bottom_left_y},
                    Point{top_right_x, top_right_y});
        rects.push_back(r);
    }
    return rects;
}
