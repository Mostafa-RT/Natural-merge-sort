cmake_minimum_required(VERSION 3.10)

project(natural_merge_sort CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB SOURCE "source/*.cpp")
# flags for compiling in debug mode
set(COMPILE_FLAGS "-Wall -Wextra -g")

include_directories(include)
set(CMAKE_CXX_FLAGS ${COMPILE_FLAGS})
add_executable(${PROJECT_NAME}.app ${SOURCE})
target_link_libraries(${PROJECT_NAME}.app m)