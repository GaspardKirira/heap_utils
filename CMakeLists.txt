cmake_minimum_required(VERSION 3.20)
project(heap_utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(heap_utils INTERFACE)
add_library(heap_utils::heap_utils ALIAS heap_utils)

target_include_directories(heap_utils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(heap_utils INTERFACE /W4 /permissive-)
else()
  target_compile_options(heap_utils INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(heap_utils_basic_test tests/test_basic.cpp)
target_link_libraries(heap_utils_basic_test PRIVATE heap_utils::heap_utils)
add_test(NAME heap_utils.basic COMMAND heap_utils_basic_test)
