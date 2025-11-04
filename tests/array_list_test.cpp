#include <cstddef>

#include "gtest/gtest.h"
#include "array_list.hpp"


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

	list.insert(999, 357);
	ASSERT_EQ(list.get_first(), 5);
	ASSERT_EQ(list.get(1), 14);
	ASSERT_EQ(list.get(2), 42);
	ASSERT_EQ(list.get_last(), 357);
}

TEST(array_list, remove) {
	auto list = ArrayList<int32_t>{};
	list.insert(0, 42);
	list.insert(0, 14);
	list.insert(0, 357);
	list.insert(0, 5);
	list.insert(0, 5);

	ASSERT_THROW(list.remove(999), std::out_of_range);
	auto length_before_remove = list.length();
	ASSERT_EQ(list.remove(list.length() - 1), 42);
	ASSERT_EQ(list.length(), length_before_remove - 1);

	ASSERT_EQ(list.remove(0), 5);
	ASSERT_EQ(list.remove(2), 14);
	ASSERT_EQ(list.remove(1), 357);
	ASSERT_THROW(list.remove(1), std::out_of_range);
	ASSERT_EQ(list.remove(0), 5);
	ASSERT_THROW(list.remove(0), std::out_of_range);

	ASSERT_TRUE(list.is_empty());

	for (size_t i = 0; i < 9; i++) {
		list.push_back(i);
	}

	for (size_t i = 0; i < list.length(); i++) {
		if (list.get(i) % 2 == 0) {
			list.remove(i);
		}
	}
	for (size_t i = 0; i < list.length(); i += 2) {
		ASSERT_TRUE(list.get(i) == static_cast<int32_t>(2 * i + 1));
	}
}
