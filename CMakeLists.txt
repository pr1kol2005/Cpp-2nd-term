project(oop-assignments)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include_directories(.)

add_subdirectory(array)
add_subdirectory(gcd)
add_subdirectory(matrix)
add_subdirectory(rational)
add_subdirectory(string_view)
add_subdirectory(sum)
