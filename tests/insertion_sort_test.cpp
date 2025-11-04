#include "gtest/gtest.h"

#include "sort.hpp"
#include "array_list.hpp"
#include <cstddef>



TEST(sort, insertion_sort) {
	auto insertion_sort = InsertionSort<int32_t>{};
	{
		auto list_empty = ArrayList<int32_t>{};
		ASSERT_NO_THROW(list_empty.sort(insertion_sort));
	}

	{
		auto list_one_element = ArrayList<int32_t>{};
		list_one_element.push_back(1);
		ASSERT_NO_THROW(list_one_element.sort(insertion_sort));
	}

	{
		auto list_two_equal_elements = ArrayList<int32_t>{};
		list_two_equal_elements.push_back(1);
		list_two_equal_elements.push_back(1);
		ASSERT_NO_THROW(list_two_equal_elements.sort(insertion_sort));
	}

	{
		auto list_many_equal_elements = ArrayList<int32_t>{};
		for (size_t i = 0; i < 9; i++) {
			list_many_equal_elements.push_back(1);
		}

		ASSERT_NO_THROW(list_many_equal_elements.sort(insertion_sort));
		for (size_t i = 0; i < list_many_equal_elements.length(); i++) {
			ASSERT_EQ(list_many_equal_elements.get(i), 1);
		}
	}

	{
		auto list_two_sorted = ArrayList<int32_t>{};

		list_two_sorted.push_back(1);
		list_two_sorted.push_back(2);
		ASSERT_NO_THROW(list_two_sorted.sort(insertion_sort));
		ASSERT_EQ(list_two_sorted.get(0), 1);
		ASSERT_EQ(list_two_sorted.get(1), 2);
	}

	{
		auto list_two_unsorted = ArrayList<int32_t>{};
		list_two_unsorted.push_back(2);
		list_two_unsorted.push_back(1);
		
		ASSERT_NO_THROW(list_two_unsorted.sort(insertion_sort));
		ASSERT_EQ(list_two_unsorted.get(0), 1);
		ASSERT_EQ(list_two_unsorted.get(1), 2);
	}

	{
		auto list_many_sorted = ArrayList<int32_t>{};
		list_many_sorted.push_back(1);
		list_many_sorted.push_back(2);
		list_many_sorted.push_back(3);
		list_many_sorted.push_back(5);
		list_many_sorted.push_back(7);
		list_many_sorted.push_back(20);
		list_many_sorted.push_back(2369);

		ASSERT_NO_THROW(list_many_sorted.sort(insertion_sort));
		ASSERT_EQ(list_many_sorted.get(0), 1);
		ASSERT_EQ(list_many_sorted.get(1), 2);
		ASSERT_EQ(list_many_sorted.get(2), 3);
		ASSERT_EQ(list_many_sorted.get(3), 5);
		ASSERT_EQ(list_many_sorted.get(4), 7);
		ASSERT_EQ(list_many_sorted.get(5), 20);
		ASSERT_EQ(list_many_sorted.get(6), 2369);
	}

	{
		auto list_many_reverse = ArrayList<int32_t>{};
		list_many_reverse.push_back(2369);
		list_many_reverse.push_back(20);
		list_many_reverse.push_back(7);
		list_many_reverse.push_back(5);
		list_many_reverse.push_back(3);
		list_many_reverse.push_back(2);
		list_many_reverse.push_back(1);

		ASSERT_NO_THROW(list_many_reverse.sort(insertion_sort));
		ASSERT_EQ(list_many_reverse.get(0), 1);
		ASSERT_EQ(list_many_reverse.get(1), 2);
		ASSERT_EQ(list_many_reverse.get(2), 3);
		ASSERT_EQ(list_many_reverse.get(3), 5);
		ASSERT_EQ(list_many_reverse.get(4), 7);
		ASSERT_EQ(list_many_reverse.get(5), 20);
		ASSERT_EQ(list_many_reverse.get(6), 2369);
	}

	{
		auto list_many_unsorted = ArrayList<int32_t>{};
		list_many_unsorted.push_back(20);
		list_many_unsorted.push_back(3);
		list_many_unsorted.push_back(7);
		list_many_unsorted.push_back(1);
		list_many_unsorted.push_back(5);
		list_many_unsorted.push_back(2369);
		list_many_unsorted.push_back(2);

		ASSERT_NO_THROW(list_many_unsorted.sort(insertion_sort));
		ASSERT_EQ(list_many_unsorted.get(0), 1);
		ASSERT_EQ(list_many_unsorted.get(1), 2);
		ASSERT_EQ(list_many_unsorted.get(2), 3);
		ASSERT_EQ(list_many_unsorted.get(3), 5);
		ASSERT_EQ(list_many_unsorted.get(4), 7);
		ASSERT_EQ(list_many_unsorted.get(5), 20);
		ASSERT_EQ(list_many_unsorted.get(6), 2369);
	}
}
