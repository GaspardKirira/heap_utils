#include <heap_utils/heap_utils.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> data{4, 8, 1, 9, 3, 7, 2, 6, 5};

  auto largest = heap_utils::largest_k(data, 3);
  auto smallest = heap_utils::smallest_k(data, 4);

  std::cout << "Largest 3: ";
  for (int x : largest)
    std::cout << x << " ";

  std::cout << "\n";

  std::cout << "Smallest 4: ";
  for (int x : smallest)
    std::cout << x << " ";

  std::cout << "\n";

  return 0;
}
