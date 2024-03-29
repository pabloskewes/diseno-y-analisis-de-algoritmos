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
        long long id;
        Node *next;
        Node(const T &value, long long id) {
            this->data = value;
            this->id = id;
            this->next = nullptr;
        }

        string toString() const {
            return "Node(data=" + data.toString() +
                   ", id=" + std::to_string(id) + ")";
        }

        void print() const {
            // std::cout << "(data: " << data << ", id: " << id << ")"
            //           << std::endl;
            std::cout << toString() << std::endl;
        }

        friend std::ostream &operator<<(std::ostream &os, const Node &node) {
            os << node.toString();
            return os;
        }
    };

    Node *head;
    Node *tail;
    int size;

    /**
     * @brief      Constructs the object.
     */
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /**
     * @brief      Pushes a back.
     * @param[in]  value  The value
     */
    void push_back(const T &value, long long id) {
        Node *newNode = new Node(value, id);
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
     * @brief      Gets a value from a given id.
     * @param[in]  id    The identifier
     * @return     The value.
     */
    T &get(long long id) const {
        Node *current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current->data;
            }
            current = current->next;
        }
        throw std::out_of_range("ID " + std::to_string(id) +
                                " not found in LinkedList");
    }

    /**
     * @brief      Prints the list.
     */
    void print() const {
        Node *current = head;
        while (current != nullptr) {
            current->print();
            current = current->next;
        }
        std::cout << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const LinkedList &linkedList) {
        Node *current = linkedList.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
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
