#include "log2.hpp"

#include <doctest.h>
#include <math.h>

static const int8_t LogTable256[256] = {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

// Source: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
int Log2floor(uint32_t v) {
    unsigned r;         // r will be lg(v)
    unsigned int t, tt; // temporaries

    if (tt = v >> 16) {
        r = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    }
    else {
        r = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
    }

    return r;
}

int Log2ceil(uint32_t v) {
    if (v == 0) {
        return -1;
    }
    else {
        return Log2floor(v - 1) + 1;
    }
}

TEST_CASE("Log2floor") {
    CHECK_EQ(Log2floor(0), -1);

    // Test 1..2^30-1
    #pragma omp parallel for default(none)
    for (int i = 0; i < 0x40; i++) {
        for (uint32_t j = 0; j <= 0x100'0000; j++) {
            auto val = (uint32_t) (i << 24 | j);

            if (val == 0) {
                continue;
            }

            CHECK_EQ(Log2floor(val), (int) floor(log2(val)));
        }
    }

    // Test 2^30..2^30 + delta
    for (uint64_t i = 0x4000'0000; i < 0x4111'1111; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2floor(val), (int) floor(log2(val)));
    }

    // Test 2^31 - delta..2^31 + delta
    for (uint64_t i = 0x7eee'eeee; i < 0x8111'1111; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2floor(val), (int) floor(log2(val)));
    }

    // Test 2^32 - delta..2^32 -1
    for (uint64_t i = 0x8eee'eeee; i <= 0xffff'ffff; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2floor(val), (int) floor(log2(val)));
    }
}

TEST_CASE("Log2ceil") {
    CHECK_EQ(Log2ceil(0), -1);

    // Test 1..2^30-1
    #pragma omp parallel for default(none)
    for (int i = 0; i < 0x40; i++) {
        for (uint32_t j = (i > 0) ? 0 : 1; j <= 0x100'0000; j++) {
            auto val = (uint32_t) (i << 24 | j);

            CHECK_EQ(Log2ceil(val), (int) ceil(log2(val)));
        }
    }

    // Test 2^30..2^30 + delta
    for (uint64_t i = 0x4000'0000; i < 0x4111'1111; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2ceil(val), (int) ceil(log2(val)));
    }

    // Test 2^31 - delta..2^31 + delta
    for (uint64_t i = 0x7eee'eeee; i < 0x8111'1111; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2ceil(val), (int) ceil(log2(val)));
    }

    // Test 2^32 - delta..2^32 -1
    for (uint64_t i = 0xeeee'eeee; i <= 0xffff'ffff; i++) {
        auto val = (uint32_t) i;
        CHECK_EQ(Log2ceil(val), (int) ceil(log2(val)));
    }
}
