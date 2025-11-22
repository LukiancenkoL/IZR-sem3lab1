/**
 * @file array_list.hpp
 * @author Lukiancenko Liza
 * @brief Dynamic array-based list implementation.
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once
/// \cond
#include <stdexcept>
#include <cstring>
#include <cstddef>
#include "gtest/gtest.h"
/// \endcond

#include "list.hpp"
#include "sort.hpp"


/**
 * @brief List implementation backed by a dynamically growing array.
 *
 * Provides amortized O(1) push_back, direct indexing, and automatic
 * reallocation when the capacity is exceeded.
 *
 * @tparam T Element type.
 */
template <typename T>
class ArrayList : public List<T> {
public:
    /**
     * @brief Construct list with default capacity (4).
     */
    ArrayList()
        : m_data(new T[4])
        , m_size(0)
        , m_capacity(4) {
    }

    /**
     * @brief Construct list with user-defined initial capacity.
     * @param capacity Initial storage size.
     */
    ArrayList(const size_t capacity)
        : m_data(new T[capacity])
        , m_size(0)
        , m_capacity(capacity) {
    }

    /**
     * @brief Sort the list using provided sorting strategy.
     * @param sort Sorting algorithm object.
     *
     */
    void sort(const Sort<T>& sort) {
        sort.sort(*this);
    }

    /**
     * @brief Get number of stored elements.
     * @return Size of list.
     */
    size_t length() const {
        return m_size;
    }

    /**
     * @brief Current allocated capacity.
     * @return Number of elements that can fit without reallocating.
     */
    size_t capacity() const {
        return m_capacity;
    }

    /**
     * @brief Append element at the end.
     * @param element Value to append.
     */
    void push_back(const T& element) {
        if (m_size >= m_capacity) {
            reallocate();
        }
        m_data[m_size++] = element;
    }

    /**
     * @brief Insert element at the beginning.
     * @param element Value to insert.
     */
    void push_front(const T& element) {
        if (m_size >= m_capacity) {
            reallocate();
        }
        std::memmove(m_data + 1, m_data, m_size * sizeof(T));
        m_data[0] = element;
        m_size++;
    }

    /**
     * @brief Get constant reference to element at index.
     * @param index Position to access.
     * @return const reference to element.
     * @throws std::out_of_range If index is invalid.
     */
    const T& get(const size_t index) const {
        if (index >= length()) {
            throw std::out_of_range("index is out of bounds");
        }
        return m_data[index];
    }

    /**
     * @brief Get first element.
     * @return const reference.
     * @throws std::out_of_range If list is empty.
     */
    const T& get_first() const {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        return get(0);
    }

    /**
     * @brief Get last element.
     * @return const reference.
     * @throws std::out_of_range If list is empty.
     */
    const T& get_last() const {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        return get(length() - 1);
    }

    /**
     * @brief Mutable access to element at index.
     * @param index Position to access.
     * @return Reference to element.
     * @throws std::out_of_range If index is invalid.
     */
    T& get_mut(const size_t index) const {
        if (index >= length()) {
            throw std::out_of_range("index is out of bounds");
        }
        return m_data[index];
    }

    /**
     * @brief Remove and return first element.
     * @return Removed element.
     * @throws std::out_of_range If list is empty.
     */
    T pop_front() {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        T first = get_first();
        std::memmove(m_data, m_data + 1, length() * sizeof(T));
        m_size--;
        return first;
    }

    /**
     * @brief Remove and return last element.
     * @return Removed element.
     * @throws std::out_of_range If list is empty.
     */
    T pop_back() {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        return m_data[--m_size];
    }

    /**
     * @brief Insert element at index (shifts others).
     *
     * If index >= size, behaves as push_back().
     *
     * @param index Insert position.
     * @param element Value to insert.
     */
    void insert(const size_t index, const T& element) {
        if (index >= length()) {
            push_back(element);
            return;
        }
        if (index == 0) {
            push_front(element);
            return;
        }
        if (m_size >= m_capacity) {
            reallocate();
        }

        std::memmove(m_data + index + 1, m_data + index,
                     (length() - index) * sizeof(T));
        m_data[index] = element;
        m_size++;
    }

    /**
     * @brief Remove and return element at index.
     * @param index Position to remove.
     * @return Removed element.
     * @throws std::out_of_range If index is invalid.
     */
    T remove(const size_t index) {
        if (index >= length()) {
            throw std::out_of_range("index is out of bounds");
        }
        T tmp = get(index);
        std::memmove(m_data + index, m_data + index + 1,
                     (length() - index - 1) * sizeof(T));
        m_size--;
        return tmp;
    }

    /**
     * @brief Check if list has no elements.
     * @return true if size == 0.
     */
    bool is_empty() const {
        return m_size == 0;
    }

    /**
     * @brief Destructor.
     *
     * Frees allocated memory.
     */
    ~ArrayList() {
        delete[] m_data;
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

private:
    /**
     * @brief Double the capacity and reallocate underlying array.
     */
    void reallocate() {
        size_t new_capacity = m_capacity * 2;
        if (new_capacity == 0) {
            new_capacity = 4;
        }
        auto new_data = new T[new_capacity];

        for (size_t i = 0; i < m_size; i++) {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }

private:
    T* m_data;         ///< Raw array storage.
    size_t m_size;     ///< Number of elements.
    size_t m_capacity; ///< Allocated capacity.

    FRIEND_TEST(array_list, reallocate);
};