#ifndef FIXED_POINT_MATH_SQRT_HPP
#define FIXED_POINT_MATH_SQRT_HPP

#include <stdint.h>

#include "log2.hpp"

// Implementation is based on http://www.cs.uni.edu/~jacobson/C++/newton.html

template <int TOLERANCE_BITS = 6, int MAX_ITERATIONS = 10>
uint32_t Sqrtu(uint32_t number) {
    if (!number) {
        // special case because call to Log2u(0) is invalid
        // better (faster + correct) solution available ?
        return 0;
    }

    int magn = Log2floor(number);
    uint32_t lower = 1 << (magn / 2);
    uint32_t upper = lower * 2;
    uint32_t tol = (lower >> TOLERANCE_BITS) + 1;

    int num_iterations = 0;

    while (upper - lower > tol && num_iterations < MAX_ITERATIONS) {
        uint32_t guess = (lower + upper) / 2;
        uint32_t squared = guess * guess;

        if (squared > number) {
            upper = guess;
        }
        else {
            lower = guess;
        }

        num_iterations++;
    }

    return (lower + upper) / 2;
}

template <int TOLERANCE_BITS = 6, int MAX_ITERATIONS = 10>
uint32_t Sqrtu(uint32_t number, int* num_iterations_out) {
    if (!number) {
        // special case because call to Log2u(0) is invalid
        // better (faster + correct) solution available ?
        *num_iterations_out = 0;
        return 0;
    }

    int magn = Log2floor(number);
    uint32_t lower = 1 << (magn / 2);
    uint32_t upper = lower * 2;
    uint32_t tol = (lower >> TOLERANCE_BITS) + 1;

    int num_iterations = 0;

    while (upper - lower > tol && num_iterations < MAX_ITERATIONS) {
        uint32_t guess = (lower + upper) / 2;
        uint32_t squared = guess * guess;

        if (squared > number) {
            upper = guess;
        }
        else {
            lower = guess;
        }

        num_iterations++;
    }

    *num_iterations_out = num_iterations;
    return (lower + upper) / 2;
}

#endif
