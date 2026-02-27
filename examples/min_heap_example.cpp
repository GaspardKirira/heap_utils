#include <heap_utils/heap_utils.hpp>
#include <iostream>
#include <vector>
#include <functional>

int main()
{
  std::vector<int> heap{7, 2, 9, 1, 5};

  heap_utils::heapify(heap.begin(), heap.end(), std::greater<>());

  std::cout << "Min-heap top: "
            << heap_utils::heap_top(heap)
            << "\n\n";

  std::cout << "Pop order:\n";
  while (!heap.empty())
  {
    std::cout << heap_utils::heap_pop(heap, std::greater<>()) << " ";
  }

  std::cout << "\n";
  return 0;
}
