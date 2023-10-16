#include "rectangle/rect_generator.hpp"
#include "libs/progressbar.hpp"
#include <iostream>
#include <random>

using namespace std;

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
 * @param show_progress_bar Whether to show a progress bar or not.
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

/**
 * Generates a sample of rectangles and writes them to a file. (Sets "R")
 * @param power The power of 2 to use for the number of rectangles to generate.
 */
void generate_input_samples(int power) {
    long long num_rects = pow(2, power);
    Point bottom_left_bound = {0, 0};
    Point top_right_bound = {500000, 500000};
    double min_side_length = 0;
    double max_side_length = 100;
    string filename = "data/rectangles/input_" + to_string(power) + ".txt";

    cout << "Generating " << num_rects << " random rectangles with side "
         << "lengths between " << min_side_length << " and " << max_side_length
         << endl
         << "and within the bounds (" << bottom_left_bound.x << ", "
         << bottom_left_bound.y << ") and (" << top_right_bound.x << ", "
         << top_right_bound.y << ")" << endl;

    vector<Rectangle> rects = generate_random_rectangles(
        num_rects, bottom_left_bound, top_right_bound, min_side_length,
        max_side_length, true);

    cout << "Generated " << rects.size() << " rectangles." << endl;

    write_rectangles_to_file(rects, filename);
}