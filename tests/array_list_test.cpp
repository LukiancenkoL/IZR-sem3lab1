/**
 * @file array_list_test.cpp
 * @author Lukiancenko Liza
 * @brief Unit tests for ArrayList.
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 * Uses GoogleTest to validate core list operations such as
 * insertion, removal, popping, and automatic reallocation.
 */

/// \cond
#include <cstddef>
#include "gtest/gtest.h"
/// \endcond
#include "array_list.hpp"

/**
 * @test Tests insertion at the front of the list.
 */
TEST(array_list, push_front) {
    auto list = ArrayList<int32_t>{};
    list.push_front(5);
    ASSERT_EQ(list.get_first(), 5);
    ASSERT_EQ(list.get_last(), 5);
    ASSERT_EQ(list.length(), 1);

    list.push_front(7);
    ASSERT_EQ(list.get_first(), 7);
    ASSERT_EQ(list.get_last(), 5);
    ASSERT_EQ(list.length(), 2);

    list.push_front(11);
    ASSERT_EQ(list.get_first(), 11);
    ASSERT_EQ(list.get(1), 7);
    ASSERT_EQ(list.get_last(), 5);
    ASSERT_EQ(list.length(), 3);
}

/**
 * @test Tests insertion at the back of the list.
 */
TEST(array_list, push_back) {
    auto list = ArrayList<int32_t>{};
    list.push_back(3);
    ASSERT_EQ(list.get_first(), 3);
    ASSERT_EQ(list.get_last(), 3);
    ASSERT_EQ(list.length(), 1);

    list.push_back(7);
    ASSERT_EQ(list.get_first(), 3);
    ASSERT_EQ(list.get_last(), 7);
    ASSERT_EQ(list.length(), 2);

    list.push_back(111);
    ASSERT_EQ(list.get_first(), 3);
    ASSERT_EQ(list.get(1), 7);
    ASSERT_EQ(list.get_last(), 111);
    ASSERT_EQ(list.length(), 3);
}

/**
 * @test Ensures pop_back removes and returns last element,
 *       and throws when the list becomes empty.
 */
TEST(array_list, pop_back) {
    auto list = ArrayList<int32_t>{};
    list.push_back(6);
    list.push_back(4);
    list.push_back(53);

    ASSERT_EQ(list.pop_back(), 53);
    ASSERT_EQ(list.get_last(), 4);

    ASSERT_EQ(list.pop_back(), 4);
    ASSERT_EQ(list.get_last(), 6);

    ASSERT_EQ(list.pop_back(), 6);
    ASSERT_EQ(list.length(), 0);

    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

/**
 * @test Ensures pop_front removes and returns first element,
 *       and throws when empty.
 */
TEST(array_list, pop_front) {
    auto list = ArrayList<int32_t>{};
    list.push_back(65);
    list.push_back(94);
    list.push_back(8);

    ASSERT_EQ(list.pop_front(), 65);
    ASSERT_EQ(list.get_first(), 94);

    ASSERT_EQ(list.pop_front(), 94);
    ASSERT_EQ(list.get_first(), 8);

    ASSERT_EQ(list.pop_front(), 8);
    ASSERT_EQ(list.length(), 0);

    ASSERT_THROW(list.pop_front(), std::out_of_range);
}

/**
 * @test Tests insertion at arbitrary positions, including
 *       inserting beyond the end (push_back behavior).
 */
TEST(array_list, insert) {
    auto list = ArrayList<int32_t>{};
    list.insert(0, 42);
    ASSERT_EQ(list.get_last(), 42);
    ASSERT_EQ(list.get_first(), 42);

    list.insert(0, 5);
    ASSERT_EQ(list.get_first(), 5);
    ASSERT_EQ(list.get_last(), 42);

    list.insert(1, 14);
    ASSERT_EQ(list.get_first(), 5);
    ASSERT_EQ(list.get(1), 14);
    ASSERT_EQ(list.get_last(), 42);

    // inserting at index > size should append
    list.insert(999, 357);
    ASSERT_EQ(list.get_last(), 357);
}

/**
 * @test Tests removal at various positions and verifies list integrity.
 */
TEST(array_list, remove) {
    auto list = ArrayList<int32_t>{};
    list.insert(0, 42);
    list.insert(0, 14);
    list.insert(0, 357);
    list.insert(0, 5);
    list.insert(0, 5);

    ASSERT_THROW(list.remove(999), std::out_of_range);

    auto len_before = list.length();
    ASSERT_EQ(list.remove(list.length() - 1), 42);
    ASSERT_EQ(list.length(), len_before - 1);

    ASSERT_EQ(list.remove(0), 5);
    ASSERT_EQ(list.remove(2), 14);
    ASSERT_EQ(list.remove(1), 357);
    ASSERT_THROW(list.remove(1), std::out_of_range);
    ASSERT_EQ(list.remove(0), 5);
    ASSERT_THROW(list.remove(0), std::out_of_range);

    ASSERT_TRUE(list.is_empty());

    // removing even numbers
    for (size_t i = 0; i < 9; i++) {
        list.push_back(i);
    }

    for (size_t i = 0; i < list.length(); i++) {
        if (list.get(i) % 2 == 0) {
            list.remove(i);
        }
    }

    // ensure odd numbers remain in increasing order
    for (size_t i = 0; i < list.length(); i += 2) {
        ASSERT_TRUE(list.get(i) == static_cast<int32_t>(2 * i + 1));
    }
}

/**
 * @test Verifies automatic reallocation as the list grows.
 */
TEST(array_list, reallocate) {
    auto list = ArrayList<int32_t>{};
    ASSERT_EQ(list.m_size, 0);
    ASSERT_EQ(list.m_capacity, 4);

    list.insert(0, 42);
    list.insert(999, 14);
    list.insert(0, 357);
    list.insert(1, 5);
    ASSERT_EQ(list.m_size, 4);
    ASSERT_EQ(list.m_capacity, 4);

    // adding more should increase capacity
    list.insert(0, 6209);
    ASSERT_EQ(list.m_capacity, 8);

    // removal should NOT decrease capacity
    list.pop_back();
    list.pop_back();
    list.pop_back();
    ASSERT_EQ(list.m_capacity, 8);

    // adding more to grow again
    for (size_t i = 0; i < 7; i++) {
        list.push_back(0);
    }
    ASSERT_EQ(list.m_capacity, 16);
}
