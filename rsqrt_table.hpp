#ifndef FIXED_POINT_MATH_RSQRT_TABLE_HPP
#define FIXED_POINT_MATH_RSQRT_TABLE_HPP

#include <stdint.h>

// 6 bits: TOTAL ERROR: 130.491425	TOTAL BIAS: 129.872681	MAX ERROR: 2.854167
// 7 bits: TOTAL ERROR: 105.218239	TOTAL BIAS: 103.872711	MAX ERROR: 1.994760
#define RSQRT_TABLE_BITS 7

#if RSQRT_TABLE_BITS == 5
extern const uint16_t rsqrt_table[33];
#endif

#if RSQRT_TABLE_BITS == 6
extern const uint16_t rsqrt_table[65];
#endif

#if RSQRT_TABLE_BITS == 7
extern const uint16_t rsqrt_table[129];
#endif

constexpr int index_mask = (1 << RSQRT_TABLE_BITS) - 1;

// Input must be >= 0x0040'0000 (1.0) and < 0x0100'0000 (4.0)
uint32_t Rsqrt_table_2_22(uint32_t input) {
    constexpr int input_bits = 24;
    constexpr int interp_bits = (input_bits - RSQRT_TABLE_BITS);

    constexpr int interp_max = (1 << interp_bits);
    constexpr int interp_mask = (1 << interp_bits) - 1;

    int index, index2, interp_pos;

    index = (input >> interp_bits) & index_mask;
    index2 = index + 1;
    interp_pos = input & interp_mask;

    int32_t interpolated = (rsqrt_table[index] + (((rsqrt_table[index2] - rsqrt_table[index]) * interp_pos + interp_max / 2) / interp_max));

    return interpolated;
}

#endif
