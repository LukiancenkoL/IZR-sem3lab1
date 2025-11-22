
/**
 * @file main.cpp
 * @author Lukiancenko Liza
 * @brief Main file
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/// \cond
#include <cstddef>
#include <print>
#include "gtest/gtest.h"
/// \endcond
#include "linked_list.hpp"
#include "sort.hpp"
#include "array_list.hpp"
#include "test_header.hpp"

int main(int argc, char** argv) {
	if (argc > 1 && argv[1] == std::string("--test")) {
		testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}

	auto a = ArrayList<int32_t>();
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_front(4);
	a.pop_front();
	a.pop_back();

	auto l = LinkedList<int32_t>();
	l.push_back(1);
	l.push_back(2);
	l.push_front(0);
	l.push_back(3);
	l.insert(2, 5);

	//Array of points
	// Point point1;
	// point1.set_point(3, 4);
	// Point point2;
	// point2.set_point(6, 0);
	// Point point3;
	// point3.set_point(-1, 7);
	// Point point4;
	// point4.set_point(5, 13);
	// auto g = ArrayList<Point>();
	// g.push_back(point1);
	// g.push_back(point2);
	// g.push_back(point3);
	// g.push_back(point4);

	InsertionSort<int32_t> insertion_sort{};
	a.sort(insertion_sort);

	std::println("merge");
	MergeSort<int32_t> m_sort{};
	a.sort(m_sort);
	std::println("merge done");

	std::println("qick");
	QuickSort<int32_t> q_sort{};
	a.sort(q_sort);
	std::println("qick done");

	std::println("Lenght: {}", l.length());
	std::println("First: {}", l.get_first());
	std::println("Last: {}", l.get_last());
	std::println("Get: {}", l.get(2));
	l.get_mut(2) = 17;
	std::println("Get_mut: {}", l.get(2));

	std::println("arg count: {}", argc);
	for (size_t i = 0; i < static_cast<size_t>(argc); i++) {
		std::println("args: {}", argv[i]);
	}

}
