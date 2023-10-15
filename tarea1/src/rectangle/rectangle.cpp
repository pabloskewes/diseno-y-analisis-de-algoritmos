#include "rectangle/rectangle.hpp"
#include "libs/progressbar.hpp"
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
double area(Rectangle rect) {
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
        Rectangle rect;
        rect.bottom_left.x = random_double(bottom_left_bound.x,
                                           top_right_bound.x - max_side_length);
        rect.bottom_left.y = random_double(bottom_left_bound.y,
                                           top_right_bound.y - max_side_length);
        rect.top_right.x = rect.bottom_left.x +
                           random_double(min_side_length, max_side_length);
        rect.top_right.y = rect.bottom_left.y +
                           random_double(min_side_length, max_side_length);
        rects.push_back(rect);
    }
    return rects;
}
