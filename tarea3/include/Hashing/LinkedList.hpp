#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

/**
 * @brief      Linked list data structure.
 * @tparam     T     Type of data to store in the list.
 */
template <typename T> struct LinkedList {
    struct Node {
        T data;
        Node *next;
        Node(const T &value) : data(value), next(nullptr) {
        }
    };

    Node *head;
    Node *tail;
    int size;

    /**
     * @brief      Constructs the object.
     */
    LinkedList() : head(nullptr), tail(nullptr), size(0) {
    }

    /**
     * @brief      Pushes a back.
     * @param[in]  value  The value
     */
    void push_back(const T &value) {
        Node *newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    /**
     * @brief      Pops the last element from the list.
     */
    void pop_back() {
        if (head == nullptr) {
            return;
        } else if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node *prev = head;
            while (prev->next != tail) {
                prev = prev->next;
            }
            delete tail;
            tail = prev;
            tail->next = nullptr;
        }
        size--;
    }

    /**
     * @brief      Prints the list.
     */
    void print() const {
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    /**
     * @brief      Tells if the list is empty.
     * @return     True if empty, False otherwise.
     */
    bool empty() const {
        return head == nullptr;
    };
};

#endif // LINKEDLIST_HPP
