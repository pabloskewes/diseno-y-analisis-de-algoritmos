#include "rectangle/test_rectangle.hpp"
#include "rectangle/rectangle.hpp"
#include "rectangle/rect_generator.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test_intersect() {
    Rectangle r1 = {{0, 0}, {1, 1}};
    Rectangle r2 = {{0.5, 0.5}, {1.5, 1.5}};
    Rectangle r3 = {{2, 2}, {3, 3}};
    Rectangle r4 = {{0, 0}, {0, 0}};

    cout << "Rectangle 1:" << endl;
    print_rectangle(r1);
    cout << "Rectangle 2:" << endl;
    print_rectangle(r2);
    cout << "Rectangle 3:" << endl;
    print_rectangle(r3);
    cout << "Rectangle 4:" << endl;
    print_rectangle(r4);

    bool r1_intersects_r2 = intersects(r1, r2);
    bool r1_intersects_r3 = intersects(r1, r3);
    bool r1_intersects_r4 = intersects(r1, r4);
    bool r2_intersects_r3 = intersects(r2, r3);
    bool r2_intersects_r4 = intersects(r2, r4);
    bool r3_intersects_r4 = intersects(r3, r4);

    cout << "r1 intersects r2: " << r1_intersects_r2 << endl;
    cout << "r1 intersects r3: " << r1_intersects_r3 << endl;
    cout << "r1 intersects r4: " << r1_intersects_r4 << endl;
    cout << "r2 intersects r3: " << r2_intersects_r3 << endl;
    cout << "r2 intersects r4: " << r2_intersects_r4 << endl;
    cout << "r3 intersects r4: " << r3_intersects_r4 << endl;
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
        print_rectangle(rects[i]);
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

void test_write_and_read_rects(int N) {
    Point bottom_left_bound = {0, 0};
    Point top_right_bound = {100, 100};
    double min_side_length = 0;
    double max_side_length = 10;

    vector<Rectangle> rects =
        generate_random_rectangles(N, bottom_left_bound, top_right_bound,
                                   min_side_length, max_side_length, false);

    string filename = "data/rectangles/small_input_test.txt";

    write_rectangles_to_file(rects, filename);

    cout << "Wrote " << rects.size() << " rectangles to " << filename << endl;

    std::vector<Rectangle> read_rects = read_rectangles_from_file(filename);

    cout << "Read " << read_rects.size() << " rectangles from " << filename
         << endl;

    for (int i = 0; i < read_rects.size(); i++) {
        cout << "Rectangle " << i << ":" << endl;
        print_rectangle(read_rects[i]);
    }
}
