#include <heap_utils/heap_utils.hpp>

#include <cassert>
#include <stdexcept>
#include <vector>

static void test_heapify_and_basic_push_pop_max_heap()
{
  std::vector<int> h{3, 1, 4, 1, 5, 9, 2};

  heap_utils::heapify(h.begin(), h.end());
  assert(heap_utils::is_heap(h.begin(), h.end()));

  // max-heap default: top is max element.
  assert(heap_utils::heap_top(h) == 9);

  heap_utils::heap_push(h, 6);
  assert(heap_utils::is_heap(h.begin(), h.end()));
  assert(heap_utils::heap_top(h) == 9);

  int a = heap_utils::heap_pop(h);
  assert(a == 9);
  assert(heap_utils::is_heap(h.begin(), h.end()));

  int b = heap_utils::heap_pop(h);
  assert(b == 6);
  assert(heap_utils::is_heap(h.begin(), h.end()));
}

static void test_min_heap_with_greater()
{
  std::vector<int> h{5, 4, 3, 2, 1};

  heap_utils::heapify(h.begin(), h.end(), std::greater<>{});
  assert(heap_utils::is_heap(h.begin(), h.end(), std::greater<>{}));

  // min-heap when using std::greater<>: top is smallest.
  assert(heap_utils::heap_top(h) == 1);

  heap_utils::heap_push(h, 0, std::greater<>{});
  assert(heap_utils::heap_top(h) == 0);

  int x = heap_utils::heap_pop(h, std::greater<>{});
  assert(x == 0);
  assert(heap_utils::heap_top(h) == 1);
}

static void test_top_k_largest_and_smallest()
{
  std::vector<int> data{7, 1, 9, 2, 8, 3, 6, 4, 5};

  const auto top3 = heap_utils::largest_k(data, 3);
  assert((top3 == std::vector<int>{9, 8, 7}));

  const auto small4 = heap_utils::smallest_k(data, 4);
  assert((small4 == std::vector<int>{1, 2, 3, 4}));

  const auto none = heap_utils::largest_k(data, 0);
  assert(none.empty());

  const auto all = heap_utils::largest_k(data, 100);
  assert(all.size() == data.size());
  assert(all.front() == 9);
  assert(all.back() == 1);
}

static void test_errors_on_empty()
{
  std::vector<int> h;

  bool threw = false;
  try
  {
    (void)heap_utils::heap_top(h);
  }
  catch (const std::runtime_error &)
  {
    threw = true;
  }
  assert(threw);

  threw = false;
  try
  {
    (void)heap_utils::heap_pop(h);
  }
  catch (const std::runtime_error &)
  {
    threw = true;
  }
  assert(threw);
}

int main()
{
  test_heapify_and_basic_push_pop_max_heap();
  test_min_heap_with_greater();
  test_top_k_largest_and_smallest();
  test_errors_on_empty();
  return 0;
}
