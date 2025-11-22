/**
 * @file sort.hpp
 * @author Lukiancenko Liza
 * @brief Sort for lists
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

/// \cond
#include <algorithm>
#include <cstddef>
#include <functional>
/// \endcond
#include "list.hpp"

/**
 * @brief Comparison result used by sorting functions.
 */
enum class Compare {
    Le = -1, ///< First < Second
    Eq = 0,  ///< First == Second
    Gr = 1,  ///< First > Second
};

/**
 * @brief Abstract base class for all sorting algorithms.
 *
 * @tparam T Type of elements stored in the List.
 */
template <typename T>
class Sort {
public:
    /**
     * @brief Sorts a given list using the provided comparison function.
     *
     * @param list List to be sorted.
     * @param compare User-defined comparator function.
     */
    virtual void sort(
        List<T>& list,
        std::function<Compare(const T& first, const T& second)> compare =
            default_compare
    ) const = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Sort() = default;

private:
    /**
     * @brief Default comparator used when no custom function is provided.
     *
     * @param first First value.
     * @param second Second value.
     * @return Compare::Gr if first > second,
     *         Compare::Le if first < second,
     *         Compare::Eq otherwise.
     */
    static Compare default_compare(const T& first, const T& second) {
        if (first > second) return Compare::Gr;
        if (first < second) return Compare::Le;
        return Compare::Eq;
    }
};

/**
 * @brief Insertion Sort implementation.
 *
 * @tparam T Type of elements.
 */
template <typename T>
class InsertionSort : public Sort<T> {
public:
    /**
     * @brief Sorts a list using the insertion sort algorithm.
     *
     * @param list List to be sorted.
     * @param compare Comparison function.
     */
    void sort(
        List<T>& list,
        std::function<Compare(const T& first, const T& second)> compare =
            Sort<T>::default_compare
    ) const {
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

/**
 * @brief Merge Sort implementation.
 *
 * @tparam T Type of elements.
 */
template <typename T>
class MergeSort : public Sort<T> {
public:
    /**
     * @brief Sorts a list using the merge sort algorithm.
     *
     * @param list List to be sorted.
     * @param compare Comparison function.
     */
    void sort(
        List<T>& list,
        std::function<Compare(const T& first, const T& second)> compare =
            Sort<T>::default_compare
    ) const {
        if (list.length() < 2) return;
        merge_sort(list, 0, list.length() - 1, compare);
    }

private:
    /**
     * @brief Recursively divides the list for merge sort.
     *
     * @param list Input list.
     * @param left Left boundary.
     * @param right Right boundary.
     * @param compare Comparison function.
     */
    void merge_sort(
        const List<T>& list,
        const size_t left,
        const size_t right,
        const std::function<Compare(const T& first, const T& second)> compare
    ) const {
        if (left >= right) return;

        const size_t mid = left + (right - left) / 2;
        merge_sort(list, left, mid, compare);
        merge_sort(list, mid + 1, right, compare);
        merge(list, left, mid, right, compare);
    }

    /**
     * @brief Merges two sorted sublists into one sorted region.
     *
     * @param list List.
     * @param left Start index of the first sublist.
     * @param mid End index of the first sublist.
     * @param right End index of the second sublist.
     * @param compare Comparison function.
     */
    void merge(
        const List<T>& list,
        const size_t left,
        const size_t mid,
        const size_t right,
        std::function<Compare(const T& first, const T& second)> compare
    ) const {
        const size_t n1 = mid - left + 1;
        const size_t n2 = right - mid;

        std::vector<T> left_vec(n1);
        std::vector<T> right_vec(n2);

        for (size_t i = 0; i < n1; i++)
            left_vec[i] = list.get(left + i);
        for (size_t i = 0; i < n2; i++)
            right_vec[i] = list.get(mid + 1 + i);

        size_t i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (compare(left_vec[i], right_vec[j]) != Compare::Gr) {
                list.get_mut(k) = left_vec[i];
                i++;
            } else {
                list.get_mut(k) = right_vec[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            list.get_mut(k) = left_vec[i];
            i++; k++;
        }
        while (j < n2) {
            list.get_mut(k) = right_vec[j];
            j++; k++;
        }
    }
};

/**
 * @brief Quick Sort implementation using dual-pivot technique.
 *
 * @tparam T Type of elements.
 */
template <typename T>
class QuickSort : public Sort<T> {
public:
    /**
     * @brief Sorts a list using the quick sort algorithm.
     *
     * @param list List to be sorted.
     * @param compare Comparison function.
     */
    void sort(
        List<T>& list,
        std::function<Compare(const T& first, const T& second)> compare =
            Sort<T>::default_compare
    ) const {
        quick_sort(list, 0, list.length() - 1, compare);
    }

private:
    /**
     * @brief Recursive dual-pivot quick sort algorithm.
     *
     * @param list List.
     * @param low Starting index.
     * @param high Ending index.
     * @param compare Comparison function.
     */
    void quick_sort(
        List<T>& list,
        int low,
        int high,
        std::function<Compare(const T& first, const T& second)> compare
    ) const {
        if (low >= high) return;

        T& pivot1 = list.get_mut(low);
        T& pivot2 = list.get_mut(high);

        if (compare(pivot1, pivot2) == Compare::Gr)
            std::swap(pivot1, pivot2);

        size_t less = low + 1;
        size_t great = high - 1;

        for (size_t k = less; k <= great; k++) {
            if (compare(list.get(k), pivot1) == Compare::Le) {
                std::swap(list.get_mut(k), list.get_mut(less));
                less++;
            } else if (compare(list.get(k), pivot2) == Compare::Gr) {
                while (k < great && compare(list.get(great), pivot2) == Compare::Gr)
                    great--;

                std::swap(list.get_mut(k), list.get_mut(great));
                great--;

                if (compare(list.get(k), pivot1) == Compare::Le) {
                    std::swap(list.get_mut(k), list.get_mut(less));
                    less++;
                }
            }
        }

        std::swap(list.get_mut(less - 1), list.get_mut(low));
        std::swap(list.get_mut(great + 1), list.get_mut(high));

        quick_sort(list, low, less - 2, compare);
        quick_sort(list, great + 2, high, compare);

        if (compare(pivot1, pivot2) != Compare::Eq) {
            for (size_t k = less; k <= great; k++) {
                if (compare(list.get(k), pivot1) == Compare::Eq) {
                    std::swap(list.get_mut(k), list.get_mut(less));
                    less++;
                } else if (compare(list.get(k), pivot2) == Compare::Eq) {
                    std::swap(list.get_mut(k), list.get_mut(great));
                    great--;
                    k--;
                }
            }
        }

        if (compare(pivot1, pivot2) == Compare::Le) {
            quick_sort(list, less, great, compare);
        }
    }
};
