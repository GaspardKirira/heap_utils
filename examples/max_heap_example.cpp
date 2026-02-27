#include <heap_utils/heap_utils.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> heap;

  heap_utils::heap_push(heap, 3);
  heap_utils::heap_push(heap, 10);
  heap_utils::heap_push(heap, 5);
  heap_utils::heap_push(heap, 1);

  std::cout << "Max-heap top: "
            << heap_utils::heap_top(heap)
            << "\n\n";

  std::cout << "Pop order:\n";
  while (!heap.empty())
  {
    std::cout << heap_utils::heap_pop(heap) << " ";
  }

  std::cout << "\n";
  return 0;
}
