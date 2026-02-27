/**
 * @file heap_utils.hpp
 * @brief Minimal heap utilities for modern C++ (push/pop/heapify/top-k).
 *
 * `heap_utils` provides small, explicit helpers built on top of std::make_heap,
 * std::push_heap, and std::pop_heap for working with heaps using vector-like
 * containers.
 *
 * Design goals:
 * - deterministic behavior (given deterministic comparator and input)
 * - minimal API surface
 * - header-only, zero dependencies
 *
 * Requirements: C++17+
 */

#ifndef HEAP_UTILS_HEAP_UTILS_HPP
#define HEAP_UTILS_HEAP_UTILS_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace heap_utils
{
  /**
   * @brief Build a heap from a container range [begin, end).
   *
   * Equivalent to std::make_heap(begin, end, comp).
   */
  template <class RandomIt, class Compare = std::less<>>
  inline void heapify(RandomIt begin, RandomIt end, Compare comp = Compare{})
  {
    std::make_heap(begin, end, comp);
  }

  /**
   * @brief Push a value into a heap (vector-style).
   *
   * This helper appends `value` to `data` and restores the heap property.
   *
   * @tparam T Element type.
   * @tparam Compare Comparator used by the heap (default: max-heap via std::less<>).
   */
  template <class T, class Compare = std::less<>>
  inline void heap_push(std::vector<T> &data, const T &value, Compare comp = Compare{})
  {
    data.push_back(value);
    std::push_heap(data.begin(), data.end(), comp);
  }

  /**
   * @brief Push a value into a heap (move).
   */
  template <class T, class Compare = std::less<>>
  inline void heap_push(std::vector<T> &data, T &&value, Compare comp = Compare{})
  {
    data.push_back(std::move(value));
    std::push_heap(data.begin(), data.end(), comp);
  }

  /**
   * @brief Return the top element of a heap.
   * @throws std::runtime_error if the heap is empty.
   */
  template <class T>
  inline const T &heap_top(const std::vector<T> &data)
  {
    if (data.empty())
    {
      throw std::runtime_error("heap_utils: heap_top() on empty heap");
    }
    return data.front();
  }

  /**
   * @brief Pop the top element of a heap and return it.
   *
   * This helper performs std::pop_heap then removes the last element.
   *
   * @throws std::runtime_error if the heap is empty.
   */
  template <class T, class Compare = std::less<>>
  inline T heap_pop(std::vector<T> &data, Compare comp = Compare{})
  {
    if (data.empty())
    {
      throw std::runtime_error("heap_utils: heap_pop() on empty heap");
    }

    std::pop_heap(data.begin(), data.end(), comp);
    T out = std::move(data.back());
    data.pop_back();
    return out;
  }

  /**
   * @brief Check if the container currently satisfies the heap property.
   */
  template <class RandomIt, class Compare = std::less<>>
  inline bool is_heap(RandomIt begin, RandomIt end, Compare comp = Compare{})
  {
    return std::is_heap(begin, end, comp);
  }

  /**
   * @brief Extract the k "best" elements according to a comparator.
   *
   * With the default comparator (std::less<>), this returns the k largest elements.
   * The result is sorted in descending order (best first for the chosen comparator).
   *
   * Notes:
   * - If k >= data.size(), returns all elements sorted accordingly.
   * - Complexity: O(n + k log n) due to heapify + k pops.
   *
   * @param data Input vector (copied internally).
   * @param k Number of elements to extract.
   * @param comp Heap comparator (same semantics as std::make_heap).
   * @return Vector of extracted elements (best first).
   */
  template <class T, class Compare = std::less<>>
  inline std::vector<T> top_k(std::vector<T> data, std::size_t k, Compare comp = Compare{})
  {
    if (k == 0 || data.empty())
    {
      return {};
    }

    heapify(data.begin(), data.end(), comp);

    const std::size_t n = data.size();
    const std::size_t kk = (k > n) ? n : k;

    std::vector<T> out;
    out.reserve(kk);

    for (std::size_t i = 0; i < kk; ++i)
    {
      out.push_back(heap_pop(data, comp));
    }

    return out;
  }

  /**
   * @brief Convenience: return the k largest elements (descending).
   *
   * Equivalent to top_k(data, k, std::less<>()).
   */
  template <class T>
  inline std::vector<T> largest_k(std::vector<T> data, std::size_t k)
  {
    return top_k(std::move(data), k, std::less<>{});
  }

  /**
   * @brief Convenience: return the k smallest elements (ascending).
   *
   * Uses a min-heap comparator (std::greater<>), then returns results in ascending order.
   */
  template <class T>
  inline std::vector<T> smallest_k(std::vector<T> data, std::size_t k)
  {
    // With std::greater<>, pop returns the smallest first (best).
    return top_k(std::move(data), k, std::greater<>{});
  }

} // namespace heap_utils

#endif // HEAP_UTILS_HEAP_UTILS_HPP
