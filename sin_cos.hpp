#ifndef FIXED_POINT_MATH_SIN_COS_HPP
#define FIXED_POINT_MATH_SIN_COS_HPP

#include <stdint.h>

// 5 bits: TOTAL ERROR: 2390.284424	TOTAL BIAS: 0.000016	MAX ERROR: 1.847876
// 6 bits: TOTAL ERROR: 1239.927612	TOTAL BIAS: -0.000005	MAX ERROR: 1.049462
// 7 bits: TOTAL ERROR: 1193.813843	TOTAL BIAS: 0.000000	MAX ERROR: 0.931593
// 8 bits: TOTAL ERROR: 1193.655884	TOTAL BIAS: 0.000008	MAX ERROR: 0.972333
#define SIN_TABLE_BITS 6

#if SIN_TABLE_BITS == 5
extern const int16_t sin_table[33];
#endif

#if SIN_TABLE_BITS == 6
extern const int16_t sin_table[65];
#endif

#if SIN_TABLE_BITS == 7
extern const int16_t sin_table[129];
#endif

constexpr int sin_table_size = (1 << SIN_TABLE_BITS) + 1;
constexpr int index_mask = (1 << SIN_TABLE_BITS) - 1;

// Input bit width is configurable, output is currently fixed at 1+12 bits (range of +/- 0x1000)
// Tabulated values are interpolated linearly, so a table of 2**6 entries already gives good results.

template <int angle_bits, typename Angle_t>
int32_t Sin(Angle_t angle) {
    // number of bits per 0.5pi radians
    constexpr int interp_bits = (angle_bits - 2 - SIN_TABLE_BITS);

    constexpr int interp_max = (1 << interp_bits);
    constexpr int interp_mask = (1 << interp_bits) - 1;

    constexpr int angle_half_bit = 1 << (angle_bits - 1);
    constexpr int angle_quarter_bit = 1 << (angle_bits - 2);

    int index, index2, interp_pos;

    if ((angle & angle_quarter_bit) == 0) {
        // 1st or 3rd quarter
        index = (angle >> interp_bits) & index_mask;
        index2 = index + 1;
        interp_pos = angle & interp_mask;
    }
    else {
        index = sin_table_size - 1 - ((angle >> interp_bits) & index_mask) - 1;
        index2 = index + 1;
        interp_pos = interp_max - (angle & interp_mask);
    }

    int32_t interpolated = (sin_table[index] + (((sin_table[index2] - sin_table[index]) * interp_pos + interp_max / 2) / interp_max));

    if ((angle & angle_half_bit) == 0) {
        return interpolated;
    }
    else {
        return -interpolated;
    }
}

template <int angle_bits, typename Angle_t>
int32_t Cos(Angle_t angle) {
    constexpr int half_pi_radians = 1 << (angle_bits - 2);

    return Sin<angle_bits, Angle_t>(angle + half_pi_radians);
}

#endif
