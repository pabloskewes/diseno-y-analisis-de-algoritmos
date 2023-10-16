#ifndef RECT_GENERATOR_HPP
#define RECT_GENERATOR_HPP

#include "rectangle/rectangle.hpp"
#include <string>
#include <vector>

using namespace std;

double random_double(double min, double max);
vector<Rectangle>
generate_random_rectangles(long long num_rects, Point bottom_left_bound,
                           Point top_right_bound, double min_side_length,
                           double max_side_length, bool show_progress_bar);

#endif // RECT_GENERATOR_HPP