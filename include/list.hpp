/**
 * @file list.hpp
 * @author 
 * @brief Abstract interface for a generic list container.
 * @version 0.1
 * @date 2025-11-16
 */

#pragma once

/// \cond
#include <cstddef>
/// \endcond

/**
 * @brief Abstract base class representing a list-like container.
 *
 * This class defines the common interface for list operations such as
 * inserting, removing, accessing elements, and checking the list state.
 * Concrete implementations (e.g., linked list, dynamic array) must override
 * all pure virtual methods.
 *
 * @tparam T Type of stored elements.
 */
template <typename T>
class List {
public:
    /**
     * @brief Returns the number of elements in the list.
     *
     * @return List size.
     */
    virtual size_t length() const = 0;

    /**
     * @brief Inserts an element at the beginning of the list.
     *
     * @param element Element to insert.
     */
    virtual void push_front(const T& element) = 0;

    /**
     * @brief Inserts an element at the end of the list.
     *
     * @param element Element to insert.
     */
    virtual void push_back(const T& element) = 0;

    /**
     * @brief Removes and returns the last element of the list.
     *
     * @return Removed element.
     * @throws std::out_of_range If the list is empty.
     */
    virtual T pop_back() = 0;

    /**
     * @brief Removes and returns the first element of the list.
     *
     * @return Removed element.
     * @throws std::out_of_range If the list is empty.
     */
    virtual T pop_front() = 0;

    /**
     * @brief Inserts an element at a specified index.
     *
     * @param index Position at which to insert the element.
     * @param element Element to insert.
     * @throws std::out_of_range If index is invalid.
     */
    virtual void insert(const size_t index, const T& element) = 0;

    /**
     * @brief Removes and returns an element at a specified index.
     *
     * @param index Position of the element to remove.
     * @return The removed element.
     * @throws std::out_of_range If index is invalid.
     */
    virtual T remove(const size_t index) = 0;

    /**
     * @brief Checks whether the list is empty.
     *
     * @return true if the list contains no elements, false otherwise.
     */
    virtual bool is_empty() const = 0;

    /**
     * @brief Returns a constant reference to the element at the given index.
     *
     * @param index Index of the element.
     * @return const reference to the element.
     * @throws std::out_of_range If index is invalid.
     */
    virtual const T& get(const size_t index) const = 0;

    /**
     * @brief Returns a mutable reference to the element at the given index.
     *
     * @param index Index of the element.
     * @return mutable reference to the element.
     * @throws std::out_of_range If index is invalid.
     */
    virtual T& get_mut(const size_t index) const = 0;

    /**
     * @brief Returns the first element of the list.
     *
     * @return const reference to the first element.
     * @throws std::out_of_range If the list is empty.
     */
    virtual const T& get_first() const = 0;

    /**
     * @brief Returns the last element of the list.
     *
     * @return const reference to the last element.
     * @throws std::out_of_range If the list is empty.
     */
    virtual const T& get_last() const = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~List() = default;
};
