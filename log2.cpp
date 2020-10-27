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

TEST_CASE("Log2floor") {
    #pragma omp parallel for default(none)
    for (int i = 0; i < 0x100; i++) {
        for (uint32_t j = 0; j <= 0x1000000; j++) {
            auto val = (uint32_t) (i << 24 | j);

            if (val == 0) {
                continue;
            }

            CHECK_EQ(Log2floor(val), (int) floor(log2(val)));
        }
    }
}
