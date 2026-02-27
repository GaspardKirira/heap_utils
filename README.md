# heap_utils

Minimal heap primitives for modern C++.

`heap_utils` provides deterministic helpers built on top of the standard
heap algorithms:

-   `std::make_heap`
-   `std::push_heap`
-   `std::pop_heap`

With a cleaner and reusable interface.

Header-only. Zero external dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/heap_utils

## Why heap_utils?

Heap problems appear everywhere:

-   Priority queues
-   Top-K queries
-   Scheduling systems
-   Streaming maximum/minimum
-   Competitive programming tasks

Using `std::priority_queue` directly often leads to:

-   Limited control over container
-   Awkward custom comparator handling
-   Repeated boilerplate
-   Harder audit of heap invariants

This library provides:

-   Explicit heapify on any vector
-   Safe push / pop helpers
-   Bounds-checked top access
-   Max-heap and min-heap support
-   Deterministic top-K extraction

No custom heap class.\
No hidden container.\
No internal allocations beyond your vector.

Just explicit heap primitives.

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/heap_utils
vix deps
```

### Manual

``` bash
git clone https://github.com/GaspardKirira/heap_utils.git
```

Add the `include/` directory to your project.

## Dependency

Requires C++17 or newer.

No external dependencies.

## Quick Examples

### Max Heap

``` cpp
#include <heap_utils/heap_utils.hpp>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> heap;

    heap_utils::heap_push(heap, 3);
    heap_utils::heap_push(heap, 10);
    heap_utils::heap_push(heap, 5);

    std::cout << heap_utils::heap_top(heap) << "\n"; // 10
}
```

### Min Heap

``` cpp
#include <heap_utils/heap_utils.hpp>
#include <iostream>
#include <vector>
#include <functional>

int main()
{
    std::vector<int> heap{5,4,3,2,1};

    heap_utils::heapify(heap.begin(), heap.end(), std::greater<>());

    std::cout << heap_utils::heap_top(heap) << "\n"; // 1
}
```

### Extract Top-K Largest

``` cpp
#include <heap_utils/heap_utils.hpp>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> data{4,8,1,9,3,7,2,6,5};

    auto largest = heap_utils::largest_k(data, 3);

    for (int x : largest)
        std::cout << x << " ";  // 9 8 7
}
```

## API Overview

``` cpp
heap_utils::heapify(begin, end, comp);

heap_utils::heap_push(vector, value, comp);
heap_utils::heap_top(vector);
heap_utils::heap_pop(vector, comp);

heap_utils::largest_k(vector, k);
heap_utils::smallest_k(vector, k);
heap_utils::top_k(vector, k, comp);
```

## Complexity

Let:

-   N = number of elements
-   K = number of extracted elements

  Operation          Time Complexity
  ------------------ -----------------
  Heapify            O(N)
  Push               O(log N)
  Pop                O(log N)
  Top-K extraction   O(N + K log N)

## Semantics

-   Default comparator (`std::less<>`) builds a **max-heap**.
-   Using `std::greater<>` builds a **min-heap**.
-   `heap_top()` and `heap_pop()` throw on empty heap.
-   Order of equal elements follows standard heap behavior.

## Design Principles

-   Explicit over implicit
-   Deterministic behavior
-   Minimal abstraction
-   Built directly on standard algorithms
-   Header-only simplicity

This library provides primitives only.

If you need:

-   Indexed priority queues
-   Mutable heap keys
-   Fibonacci heap
-   Pairing heap
-   Advanced scheduling policies

Build them on top of this layer.

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Heap property correctness
-   Max-heap and min-heap behavior
-   Top-K extraction
-   Error handling

## License

MIT License\
Copyright (c) Gaspard Kirira

