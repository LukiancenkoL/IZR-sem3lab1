#pragma once
#include "list.hpp"
// #include <vector>
// #include <memory>
#include <algorithm>
#include <cstddef>
#include <functional>

enum class Compare {
	Le = -1,
	Eq = 0,
	Gr = 1,
};

template <typename T>
class Sort {
public:
	virtual void sort(List<T>& list,
			std::function<Compare(const T& first, const T& second)> compare =
					default_compare) const = 0;
	virtual ~Sort() = default;

private:
	static Compare default_compare(const T& first, const T& second) {
		if (first > second) {
			return Compare::Gr;
		}
		if (first < second) {
			return Compare::Le;
		}
		return Compare::Eq;
	}
};

template <typename T>
class InsertionSort : public Sort<T> {
public:
	void sort(List<T>& list,
			std::function<Compare(const T& first, const T& second)> compare =
					Sort<T>::default_compare) const {
		for (size_t i = 1; i < list.length(); i++) {
			T key = list.get(i);

			int32_t j = i - 1;
			while (j >= 0 && compare(list.get(j), key) == Compare::Gr) {
				list.get_mut(j + 1) = list.get(j);
				j -= 1;
			}

			list.get_mut(j + 1) = key;
		}
	}
};

template <typename T>
class MergeSort : public Sort<T> {
public:
	void sort(List<T>& list,
			std::function<Compare(const T& first, const T& second)> compare =
					Sort<T>::default_compare) const {
		if (list.length() < 2) {
			return;
		}
		merge_sort(list, 0, list.length() - 1, compare);
	}

private:
	void merge_sort(const List<T>& list, const size_t left, const size_t right,
			const std::function<Compare(const T& first, const T& second)> compare) const {
		if (left >= right) {
			return;
		}
		const size_t mid = left + (right - left) / 2;
		merge_sort(list, left, mid, compare);
		merge_sort(list, mid + 1, right, compare);
		merge(list, left, mid, right, compare);
	}

	void merge(const List<T>& list, const size_t left, const size_t mid, const size_t right,
			std::function<Compare(const T& first, const T& second)> compare) const {
		const size_t n1 = mid - left + 1;
		const size_t n2 = right - mid;

		std::vector<T> left_vec(n1);
		std::vector<T> right_vec(n2);

		for (size_t i = 0; i < n1; i++) {
			left_vec[i] = list.get(left + i);
		}
		for (size_t i = 0; i < n2; i++) {
			right_vec[i] = list.get(mid + 1 + i);
		}

		size_t i = 0;
		size_t j = 0;
		size_t k = left;

		while (i < n1 && j < n2) {
			if (compare(left_vec[i], right_vec[j]) != Compare::Gr) {
				list.get_mut(k) = left_vec[i];
				i += 1;
			} else {
				list.get_mut(k) = right_vec[j];
				j += 1;
			}
			k += 1;
		}

		while (i < n1) {
			list.get_mut(k) = left_vec[i];
			i += 1;
			k += 1;
		}
		while (j < n2) {
			list.get_mut(k) = right_vec[j];
			j += 1;
			k += 1;
		}
	}
};

template <typename T>
class QuickSort : public Sort<T> {
public:
	void sort(List<T>& list,
			std::function<Compare(const T& first, const T& second)> compare =
					Sort<T>::default_compare) const {
		quick_sort(list, 0, list.length() - 1, compare);
	}

private:
	void quick_sort(List<T>& list, int low, int high,
			std::function<Compare(const T& first, const T& second)> compare) const {
		if (low >= high) {
			return;
		}
		T& pivot1 = list.get_mut(low);
		T& pivot2 = list.get_mut(high);
		if (compare(pivot1, pivot2) == Compare::Gr) {
			std::swap(pivot1, pivot2);
		}

		size_t less = low + 1;
		size_t great = high - 1;
		for (size_t k = less; k <= great; k++) {
			if (compare(list.get(k), pivot1) == Compare::Le) {
				std::swap(list.get_mut(k), list.get_mut(less));
				less += 1;
			} else if (compare(list.get(k), pivot2) == Compare::Gr) {
				while (k < great && compare(list.get(great), pivot2) == Compare::Gr) {
					great -= 1;
				}
				std::swap(list.get_mut(k), list.get_mut(great));
				great -= 1;
				if (compare(list.get(k), pivot1) == Compare::Le) {
					std::swap(list.get_mut(k), list.get_mut(less));
					less += 1;
				}
			}
		}

		std::swap(list.get_mut(less - 1), list.get_mut(low));
		std::swap(list.get_mut(great + 1), list.get_mut(high));

		// low, high must be int, not uint, because in case of length == 2
		// low == 0, high == 1, less == 1, great == 0
		// k == less -> k == 1 -> (k > great) -> for loop never happens
		// (less - 2) == -1 -> underflows as unit -> (low >= high) doesn't work
		quick_sort(list, low, less - 2, compare);
		quick_sort(list, great + 2, high, compare);

		if (compare(pivot1, pivot2) != Compare::Eq) {
			for (size_t k = less; k <= great; k++) {
				if (compare(list.get(k), pivot1) == Compare::Eq) {
					std::swap(list.get_mut(k), list.get_mut(less));
					less += 1;
				} else if (compare(list.get(k), pivot2) == Compare::Eq) {
					std::swap(list.get_mut(k), list.get_mut(great));
					great -= 1;

					// we need to decrement k,
					// so the element which we swapped with List on this iteration
					// will be compared to pivot1 on the next iteration
					k -= 1;
				}
			}
		}
		if (compare(pivot1, pivot2) == Compare::Le) {
			quick_sort(list, less, great, compare);
		}
	}
};
