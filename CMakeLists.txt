cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -DDEBUG")
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
)
