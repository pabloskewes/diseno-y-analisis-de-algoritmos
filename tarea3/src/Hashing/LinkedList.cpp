#include "Hashing/LinkedList.hpp"

/**
 * @brief      Constructs the object.
 */
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {
}

/**
 * @brief      Pushes a back.
 * @param[in]  value  The value
 */
void LinkedList<T>::push_back(const T &value) {
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
 * @brief      Pops a back from the list.
 */
void LinkedList<T>::pop_back() {
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
 * @brief      Clears the list.
 */
void LinkedList<T>::clear() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
 * @brief      Prints the list.
 */
void LinkedList<T>::print() const {
    Node *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
