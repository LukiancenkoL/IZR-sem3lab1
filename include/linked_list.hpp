/**
 * @file linked_list.hpp
 * @author 
 * @brief Implementation of a doubly linked list based on the List interface.
 * @version 0.1
 * @date 2025-11-16
 */

#pragma once

/// \cond
#include <cstddef>
#include <stdexcept>
#include <cstring>
/// \endcond
#include "list.hpp"

/**
 * @brief Node structure used in a doubly linked list.
 *
 * Each node stores an element, a pointer to the previous node,
 * and a pointer to the next node.
 *
 * @tparam T Type of the stored element.
 */
template <typename T>
class Node {
public:
    /**
     * @brief Constructs a node holding the given element.
     *
     * @param element Value to store in the node.
     */
    Node(const T& element)
        : m_prev(nullptr)
        , m_next(nullptr)
        , m_data(element) {
    }

    /**
     * @brief Sets the pointer to the previous node.
     *
     * @param new_value Pointer to the previous node.
     */
    void set_prev(Node* new_value) {
        this->m_prev = new_value;
    }

    /**
     * @brief Sets the pointer to the next node.
     *
     * @param new_value Pointer to the next node.
     */
    void set_next(Node* new_value) {
        this->m_next = new_value;
    }

    /**
     * @brief Returns the stored data (read-only).
     *
     * @return const reference to stored data.
     */
    const T& get_data() {
        return this->m_data;
    }

    /**
     * @brief Returns mutable reference to stored data.
     *
     * @return reference to stored data.
     */
    T& get_data_mut() {
        return this->m_data;
    }

    /**
     * @brief Returns pointer to the next node.
     *
     * @return Pointer to next node, or nullptr.
     */
    Node* get_next() {
        return this->m_next;
    }

    /**
     * @brief Returns pointer to the previous node.
     *
     * @return Pointer to previous node, or nullptr.
     */
    Node* get_prev() {
        return this->m_prev;
    }

private:
    Node* m_prev; ///< Pointer to previous node.
    Node* m_next; ///< Pointer to next node.
    T m_data;     ///< Stored element.
};

/**
 * @brief Doubly linked list implementation of the List interface.
 *
 * Provides insertion, removal, forward traversal, and access operations.
 *
 * @tparam T Type of stored elements.
 */
template <typename T>
class LinkedList : public List<T> {
public:

    /**
     * @brief Returns the number of elements stored in the list.
     *
     * @return Number of elements.
     */
    size_t length() const {
        return this->m_size;
    }

    /**
     * @brief Inserts an element at the beginning of the list.
     *
     * @param element Element to insert.
     */
    void push_front(const T& element) {
        Node<T>* node = new Node(element);
        if (this->is_empty()) {
            this->m_head = node;
            this->m_tail = node;
        }

        this->m_head->set_prev(node);
        node->set_next(this->m_head);
        this->m_head = node;
        this->m_size += 1;
    }

    /**
     * @brief Inserts an element at the end of the list.
     *
     * @param element Element to insert.
     */
    void push_back(const T& element) {
        Node<T>* node = new Node(element);
        if (this->is_empty()) {
            this->m_head = node;
            this->m_tail = node;
        }

        this->m_tail->set_next(node);
        node->set_prev(this->m_tail);
        this->m_tail = node;
        this->m_size += 1;
    }

    /**
     * @brief Removes and returns the last element.
     *
     * @return The removed element.
     * @throws std::out_of_range If the list is empty.
     */
    T pop_back() {
        if (this->is_empty()) {
            throw std::out_of_range("List is empty");
        }
        T last = this->get_last();
        this->m_tail = this->m_tail->get_prev();
        delete this->m_tail->get_next();
        this->m_tail->set_next(nullptr);
        this->m_size -= 1;
        return last;
    }

    /**
     * @brief Removes and returns the first element of the list.
     *
     * @return The removed element.
     * @throws std::out_of_range If the list is empty.
     */
    T pop_front() {
        if (this->is_empty()) {
            throw std::out_of_range("List is empty");
        }
        if (this->length() == 1) {
            const auto tmp = this->get_first();
            delete this->m_head;
            this->m_head = nullptr;
            this->m_tail = nullptr;
            this->m_size = 0;
            return tmp;
        }
        const auto first = this->get_first();
        this->m_head = this->m_head->get_next();
        delete this->m_head->get_prev();
        this->m_head->set_prev(nullptr);
        this->m_size -= 1;
        return first;
    }

    /**
     * @brief Inserts an element at a specific index.
     *
     * If the index is equal to or larger than the size, the element is appended.
     *
     * @param index Position to insert the element.
     * @param element Element to insert.
     */
    void insert(const size_t index, const T& element) {
        if (index >= this->length()) {
            this->push_back(element);
            return;
        }

        if (index == 0) {
            this->push_front(element);
            return;
        }

        Node<T>* curr = this->m_head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->get_next();
        }
        Node<T>* node = new Node(element);

        node->set_next(curr);
        node->set_prev(curr->get_prev());
        curr->get_prev()->set_next(node);
        curr->set_prev(node);
        this->m_size += 1;
    }

    /**
     * @brief Removes and returns an element at a given index.
     *
     * @param index Index of the element to remove.
     * @return The removed element.
     * @throws std::out_of_range If index is invalid.
     */
    T remove(const size_t index) {
        if (index >= this->length()) {
            throw std::out_of_range("index is out of bounds");
        }
        if (this->length() == 1) {
            const auto tmp = this->get_first();
            delete this->m_head;
            this->m_head = nullptr;
            this->m_tail = nullptr;
            this->m_size = 0;
            return tmp;
        }
        if (index == 0) {
            const auto first = this->get_first();
            this->m_head = this->m_head->get_next();
            delete this->m_head->get_prev();
            this->m_head->set_prev(nullptr);
            this->m_size -= 1;
            return first;
        }
        if (index == this->length() - 1) {
            const auto last = this->get_last();
            this->m_tail = this->m_tail->get_prev();
            delete this->m_tail->get_next();
            this->m_tail->set_next(nullptr);
            this->m_size -= 1;
            return last;
        }
        auto* curr = this->m_head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->get_next();
        }
        const auto tmp = curr->get_data();
        auto* prev = curr->get_prev();
        auto* next = curr->get_next();
        delete curr;

        prev->set_next(next);
        next->set_prev(prev);
        this->m_size -= 1;
        return tmp;
    }

    /**
     * @brief Checks if the list is empty.
     *
     * @return true if size == 0, otherwise false.
     */
    bool is_empty() const {
        return this->length() == 0;
    }

    /**
     * @brief Returns the element at a given index.
     *
     * @param index Index to access.
     * @return const reference to the element.
     * @throws std::out_of_range If index is invalid.
     */
    const T& get(const size_t index) const {
        if (index >= this->length()) {
            throw std::out_of_range("index is out of bounds");
        }

        Node<T>* current = this->m_head;
        for (size_t i = 0; i < index; i++) {
            current = current->get_next();
        }

        return current->get_data();
    }

    /**
     * @brief Returns a mutable reference to the element at a given index.
     *
     * @param index Index to access.
     * @return reference to element.
     * @throws std::out_of_range If index is invalid.
     */
    T& get_mut(const size_t index) const {
        if (index >= this->length()) {
            throw std::out_of_range("index is out of bounds");
        }

        Node<T>* current = this->m_head;
        for (size_t i = 0; i < index; i++) {
            current = current->get_next();
        }

        return current->get_data_mut();
    }

    /**
     * @brief Returns the first element in the list.
     *
     * @return const reference to the first element.
     * @throws std::out_of_range If the list is empty.
     */
    const T& get_first() const {
        if (this->is_empty() || this->m_head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return this->m_head->get_data();
    }

    /**
     * @brief Returns the last element in the list.
     *
     * @return const reference to the last element.
     * @throws std::out_of_range If the list is empty.
     */
    const T& get_last() const {
        if (this->is_empty() || this->m_tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return this->m_tail->get_data();
    }

private:
    Node<T>* m_head = nullptr; ///< Pointer to the first element.
    Node<T>* m_tail = nullptr; ///< Pointer to the last element.
    size_t m_size = 0;         ///< Number of elements in the list.
};
