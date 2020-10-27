cmake_minimum_required(VERSION 3.12)
project(Fixed_Point_Math CXX)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_SRC
        log2.cpp
        log2.hpp
        sqrt.cpp
        sqrt.hpp
)

add_library(Fixed_Point_Math STATIC
        ${LIBRARY_SRC}
        )

target_include_directories(Fixed_Point_Math PRIVATE include)

add_executable(tests doctest-main.cpp ${LIBRARY_SRC})
target_include_directories(tests PRIVATE include)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(tests PUBLIC OpenMP::OpenMP_CXX)
endif()
