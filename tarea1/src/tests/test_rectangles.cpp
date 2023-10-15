#include "rectangle/rectangle.hpp"
#include "libs/progressbar.hpp"
#include <iostream>


void test_intersect() {
    Rectangle r1 = {{0, 0}, {1, 1}};
    Rectangle r2 = {{0.5, 0.5}, {1.5, 1.5}};
    Rectangle r3 = {{2, 2}, {3, 3}};
    Rectangle r4 = {{0, 0}, {0, 0}};

    std::cout << "Rectangle 1:" << std::endl;
    std::cout << "Bottom left: (" << r1.bottom_left.x << ", "
              << r1.bottom_left.y << ")" << std::endl;
    std::cout << "Top right: (" << r1.top_right.x << ", " << r1.top_right.y
              << ")" << std::endl;

    std::cout << "Rectangle 2:" << std::endl;
    std::cout << "Bottom left: (" << r2.bottom_left.x << ", "
              << r2.bottom_left.y << ")" << std::endl;
    std::cout << "Top right: (" << r2.top_right.x << ", " << r2.top_right.y
              << ")" << std::endl;

    std::cout << "Rectangle 3:" << std::endl;
    std::cout << "Bottom left: (" << r3.bottom_left.x << ", "
              << r3.bottom_left.y << ")" << std::endl;
    std::cout << "Top right: (" << r3.top_right.x << ", " << r3.top_right.y
              << ")" << std::endl;

    std::cout << "Rectangle 4:" << std::endl;
    std::cout << "Bottom left: (" << r4.bottom_left.x << ", "
              << r4.bottom_left.y << ")" << std::endl;
    std::cout << "Top right: (" << r4.top_right.x << ", " << r4.top_right.y
              << ")" << std::endl;

    bool r1_intersects_r2 = intersects(r1, r2);
    bool r1_intersects_r3 = intersects(r1, r3);
    bool r1_intersects_r4 = intersects(r1, r4);
    bool r2_intersects_r3 = intersects(r2, r3);
    bool r2_intersects_r4 = intersects(r2, r4);
    bool r3_intersects_r4 = intersects(r3, r4);

    std::cout << "r1 intersects r2: " << r1_intersects_r2 << std::endl;
    std::cout << "r1 intersects r3: " << r1_intersects_r3 << std::endl;
    std::cout << "r1 intersects r4: " << r1_intersects_r4 << std::endl;
    std::cout << "r2 intersects r3: " << r2_intersects_r3 << std::endl;
    std::cout << "r2 intersects r4: " << r2_intersects_r4 << std::endl;
    std::cout << "r3 intersects r4: " << r3_intersects_r4 << std::endl;
}

void test_generate_random_rects() {
    Point bottom_left_bound = {0, 0};
    Point top_right_bound = {10, 10};
    double min_side_length = 1;
    double max_side_length = 7;
    int num_rects = 10;

    std::cout << "Generating " << num_rects << " random rectangles with side "
              << "lengths between " << min_side_length << " and "
              << max_side_length << std::endl
              << "and within the bounds (" << bottom_left_bound.x << ", "
              << bottom_left_bound.y << ") and (" << top_right_bound.x << ", "
              << top_right_bound.y << ")" << std::endl;

    std::vector<Rectangle> rects = generate_random_rectangles(
        num_rects, bottom_left_bound, top_right_bound, min_side_length,
        max_side_length, false);

    for (int i = 0; i < rects.size(); i++) {
        std::cout << "Rectangle " << i << ":" << std::endl;
        std::cout << "Bottom left: (" << rects[i].bottom_left.x << ", "
                  << rects[i].bottom_left.y << ")" << std::endl;
        std::cout << "Top right: (" << rects[i].top_right.x << ", "
                  << rects[i].top_right.y << ")" << std::endl;
    }
}

void test_generate_random_rects_massive(long long N) {
    Point bottom_left_bound = {0, 0};
    Point top_right_bound = {500000, 500000};
    double min_side_length = 0;
    double max_side_length = 100;
    int num_rects = N;

    std::cout << "Generating " << num_rects << " random rectangles with side "
              << "lengths between " << min_side_length << " and "
              << max_side_length << std::endl
              << "and within the bounds (" << bottom_left_bound.x << ", "
              << bottom_left_bound.y << ") and (" << top_right_bound.x << ", "
              << top_right_bound.y << ")" << std::endl;

    std::vector<Rectangle> rects = generate_random_rectangles(
        num_rects, bottom_left_bound, top_right_bound, min_side_length,
        max_side_length, true);

    std::cout << "Generated " << rects.size() << " rectangles." << std::endl;
}