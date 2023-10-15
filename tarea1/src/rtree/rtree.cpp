#include "rtree/rtree.hpp"
#include "rectangle/rectangle.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    vector<Node> children;
    vector<Rectangle> rectangles;
    bool is_leaf;
    Node *parent;

    Node(vector<Rectangle> rectangles, bool is_leaf, Node *parent) {
        this->rectangles = rectangles;
        this->is_leaf = is_leaf;
        this->parent = parent;
    }
};

class RTree {
  public:
    Node *root;

    RTree() {
        this->root = new Node(vector<Rectangle>(), true, nullptr);
    }

    void insert(Rectangle rect) {
        Node *leaf = choose_leaf(rect);
        leaf->rectangles.push_back(rect);
        if (leaf->rectangles.size() > 4) {
            split_node(leaf);
        }
    }

    Node *choose_leaf(Rectangle rect) {
        Node *node = this->root;
        while (!node->is_leaf) {
            node = choose_subtree(node, rect);
        }
        return node;
    }

    Node *choose_subtree(Node *node, Rectangle rect) {
        Node *best_child = nullptr;
        double best_area = 0;
        for (Node child : node->children) {
            double area = rectangle_area(child.rectangles[0]);
            if (best_child == nullptr || area < best_area) {
                best_child = &child;
                best_area = area;
            }
        }
        return best_child;
    }

    void split_node(Node *node) {
        vector<Rectangle> rectangles = node->rectangles;
        vector<Rectangle> best_group1;
        vector<Rectangle> best_group2;
        double best_difference = 0;
        for (int i = 0; i < rectangles.size(); i++) {
            for (int j = i + 1; j < rectangles.size(); j++) {
                vector<Rectangle> group1;
                vector<Rectangle> group2;
                for (int k = 0; k < rectangles.size(); k++) {
                    if (k <= i || k <= j) {
                        group1.push_back(rectangles[k]);
                    } else {
                        group2.push_back(rectangles[k]);
                    }
                }
                double difference = abs(rectangle_area(group1[0]) - rectangle_area(group2[0]));
                if (best_group1.size() == 0 || difference < best_difference) {
                    best_group1 = group1;
                    best_group2 = group2;
                    best_difference = difference;
                }
            }
        }
        node->rectangles = best_group1;
        Node *new_node = new Node(best_group2, node->is_leaf, node->parent);
        node->parent->children.push_back(*new_node);
    }
};
