/**
 * @file quick_sort_test.cpp
 * @author Lukiancenko Liza
 * @brief Unit tests for QuickSort.
 * @version 0.1
 * @date 2025-11-18
 * 
 * @copyright Copyright (c) 2025
 * 
 * Covers edge cases (empty, single element, duplicates)
 * and typical scenarios (sorted, reversed, random input).
 */
 /// \cond
#include "gtest/gtest.h"
#include <cstddef>
/// \endcond
#include "sort.hpp"
#include "array_list.hpp"


/**
 * @test Tests QuickSort with various input configurations.
 */
TEST(sort, quick_sort) {
    auto quick_sort = QuickSort<int32_t>{};

    // empty list
    {
        auto list = ArrayList<int32_t>{};
        ASSERT_NO_THROW(list.sort(quick_sort));
    }

    // one element
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(1);
        ASSERT_NO_THROW(list.sort(quick_sort));
    }

    // two equal elements
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(1);
        list.push_back(1);
        ASSERT_NO_THROW(list.sort(quick_sort));
    }

    // many equal elements
    {
        auto list = ArrayList<int32_t>{};
        for (size_t i = 0; i < 9; i++) list.push_back(1);
        ASSERT_NO_THROW(list.sort(quick_sort));
        for (size_t i = 0; i < list.length(); i++) ASSERT_EQ(list.get(i), 1);
    }

    // already sorted (two elements)
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(1);
        list.push_back(2);
        ASSERT_NO_THROW(list.sort(quick_sort));
        ASSERT_EQ(list.get(0), 1);
        ASSERT_EQ(list.get(1), 2);
    }

    // unsorted (two elements)
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(2);
        list.push_back(1);
        ASSERT_NO_THROW(list.sort(quick_sort));
        ASSERT_EQ(list.get(0), 1);
        ASSERT_EQ(list.get(1), 2);
    }

    // already sorted (many elements)
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(5);
        list.push_back(7);
        list.push_back(20);
        list.push_back(2369);

        ASSERT_NO_THROW(list.sort(quick_sort));
        ASSERT_EQ(list.get(0), 1);
        ASSERT_EQ(list.get(1), 2);
        ASSERT_EQ(list.get(2), 3);
        ASSERT_EQ(list.get(3), 5);
        ASSERT_EQ(list.get(4), 7);
        ASSERT_EQ(list.get(5), 20);
        ASSERT_EQ(list.get(6), 2369);
    }

    // reversed
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(2369);
        list.push_back(20);
        list.push_back(7);
        list.push_back(5);
        list.push_back(3);
        list.push_back(2);
        list.push_back(1);

        ASSERT_NO_THROW(list.sort(quick_sort));
        ASSERT_EQ(list.get(0), 1);
        ASSERT_EQ(list.get(1), 2);
        ASSERT_EQ(list.get(2), 3);
        ASSERT_EQ(list.get(3), 5);
        ASSERT_EQ(list.get(4), 7);
        ASSERT_EQ(list.get(5), 20);
        ASSERT_EQ(list.get(6), 2369);
    }

    // random unsorted input
    {
        auto list = ArrayList<int32_t>{};
        list.push_back(20);
        list.push_back(3);
        list.push_back(7);
        list.push_back(1);
        list.push_back(5);
        list.push_back(2369);
        list.push_back(2);

        ASSERT_NO_THROW(list.sort(quick_sort));
        ASSERT_EQ(list.get(0), 1);
        ASSERT_EQ(list.get(1), 2);
        ASSERT_EQ(list.get(2), 3);
        ASSERT_EQ(list.get(3), 5);
        ASSERT_EQ(list.get(4), 7);
        ASSERT_EQ(list.get(5), 20);
        ASSERT_EQ(list.get(6), 2369);
    }
}
