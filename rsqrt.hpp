#ifndef FIXED_POINT_MATH_SQRT_HPP
#define FIXED_POINT_MATH_SQRT_HPP

#include <stdint.h>

#include "log2.hpp"

// Approach:
// Given x, find approximate y = 1/sqrt(x)
// The decimal value x is encoded in a 20.12 fixed-point format as value X of length N+1 bits (N = log2floor X);
// similarly, the result y is returned in a 20.12 fixed-point format as Y of M+1 bits.
//
// We can also say:  x = 2**n,
// therefore:        y = 2**(-n/2).
// This lets us set a lower bound as y >= 2**(floor(-ceil(n) / 2))) and an upper bound on y as y <= 2**(ceil(-floor(n) / 2))
//
// In our fixed-point format, this corresponds to 2**((3*F - N - 1) // 2) <= Y <= 2**((3*F - N + 1) // 2)
// (with F=12 specifying the number of fractional bits and the operator "//" denoting integer division rounded towards 0 or negative infinity)
//
// Having established these bounds, we can proceed using the method of interval halving, which generates approximately
// 1 bit of precision per iteration.
// On every iteration, we check if x * y_estimate**2 is lower or greater than 1, and we adjust the bounds correspondingly.
//
// We have to watch out for integer overflow, because the naive calculation of X * Y_est**2 would generate values up to
//   2**n * 2**(ceil(-floor(n) / 2)) * 2**(ceil(-floor(n) / 2)) * 2**(3*F), or
//   2**(3*F + 2) - 1 in the worst case. For F=12 that will overflow the 32-bit unsigned integer format. Thus, to ensure
// that X * Y_est**2 is always < 2**32, we right-shift the multiplicands to drop some bits. To keep things simple(-ish),
// let us say that we choose a threshold T such that:
//   for N >= T, we calculate (X >> S) * Y_estimate * Y_estimate             where 3*F + 2 - S = 32           (case Cx)
//   for N <  T, we calculate X * (Y_estimate >> S1) * (Y_estimate >> S2)    where 3*F + 2 - S1 - S2 = 31.    (case Cy)
//
// To select an optimal T, we need to quantify the relative error due to the dropped bits.
// For the case Cx, the maximum absolute X-error is 2**S - 1. The maximum relative error will then be
//   err_rel_Cx = (2**S - 1) / X_min = (2**S - 1) / 2**T.
// (increasing T decreases the relative error)
//
// For the case Cy, we need to do a bit more arithmetic. From the (a + b)(a + c) formula we can see that in the worst case,
// we will over/under-estimate Y_est**2 by
//   (2**S1 - 1) * Y_est + (2**S2 - 1) * Y_est + (2**S1 - 1) * (2**S2 - 1).
// The relative error will be maximized for the minimum Y, which is calculated as follows:
//   X_max = 2**(T + 1) - 1
//   Y_min = floor(2**(3*F/2) / sqrt(X_max))
//   err_rel_Cy = ((2**S1 - 1) * Y_est + (2**S2 - 1) * Y_est + (2**S1 - 1) * (2**S2 - 1)) / (Y_min ** 2).
// (it might not be obvious immediately here, but increasing T increases the relative error)
//
// Then it is simply a matter of finding such T that minimizes the maximum of (err_rel_Cx, err_rel_Cy).
// The attached script rsqrt-bits.py does exactly that (by enumeration, since there are only 32 possibilities for T);
// for F=12, the optimum is T=13.


// Implementation is inspired by Sqrt from http://www.cs.uni.edu/~jacobson/C++/newton.html
template <int TOLERANCE_BITS = 6, int MAX_ITERATIONS = 10>
uint32_t Rsqrt_iter(uint32_t number, int* num_iterations_out) {
    if (!number) {
        *num_iterations_out = 0;
        return 0xffff'ffff;
    }

    constexpr int Thres = 13;
    constexpr int F = 12;

    int magn = Log2floor(number);

    auto M_lb = (3 * F - magn - 1) / 2;
    auto M_ub = (3 * F - magn + 1) / 2;

    uint32_t lower = 1 << M_lb;
    uint32_t upper = 1 << M_ub;
    uint32_t tol = (lower >> TOLERANCE_BITS) + 1;

    int num_iterations = 0;

    if (magn >= Thres) {
        while (upper - lower > tol && num_iterations < MAX_ITERATIONS) {
            uint32_t guess = (lower + upper) / 2;
            uint32_t squared = guess * guess * (number >> 6);

            if (squared > 0x4000'0000) {
                upper = guess;
            } else {
                lower = guess;
            }

            num_iterations++;
        }
    }
    else  {
        while (upper - lower > tol && num_iterations < MAX_ITERATIONS) {
            uint32_t guess = (lower + upper) / 2;
            uint32_t squared = (guess >> 3) * (guess >> 3) * number;

            if (squared > 0x4000'0000) {
                upper = guess;
            } else {
                lower = guess;
            }

            num_iterations++;
        }
    }

    *num_iterations_out = num_iterations;
    return (lower + upper) / 2;
}

#endif
