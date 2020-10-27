#include "rsqrt.hpp"

#include <doctest.h>
#include <math.h>
#include <stdio.h>

// TODO: quantify required/achieved absolute/relative tolerance

static void RsqrtDemo1(double number) {
    if (number * 4096.0 > UINT32_MAX) {
        return;
    }

    int num_iterations;
    int input_int = (int)(number * 4096.0);
    int eval = Rsqrt_iter(input_int, &num_iterations);

    double correct_result = 4096.0 / sqrt(number);
    int correct_eval = (int)round(correct_result);

    double error = (eval != correct_eval) ? (double)(eval - correct_result) / correct_result : 0;

    if (abs(error) > 1) {
        error = NAN;
    }

    // Uncomment this to print out a lot of info
    printf("rsqrt(%14.2f) -> %12.3f vs %9.3f, %+7.2f%% error // (%10u) -> %12d vs %12d [%+12d after %2d iterations]\n",
           number, eval / 4096.0, correct_result / 4096.0, error * 100,
           (unsigned int)(number * 16777216.0), eval, correct_eval,
           eval - correct_eval, num_iterations);
    // Uncomment this to generate test assertions
//    printf("CHECK_LE(abs((int) Rsqrt_iter(%10d) - (int) round(4096.0 / sqrt(%10d / 4096.0))), %3d);\n", input_int, input_int,
//           1 + correct_eval / 100);
}

static void RsqrtGenerateAssertions() {
    for (int i = -14; i < 60; i++) {
        RsqrtDemo1(pow(10, i * 0.25));
    }

    for (int i = 1; i < 32; i++) {
        RsqrtDemo1(pow(2, i));
    }

    RsqrtDemo1(1 / 4096.0);
    RsqrtDemo1(2 / 4096.0);
    RsqrtDemo1(3 / 4096.0);
    RsqrtDemo1(4 / 4096.0);
    RsqrtDemo1(0.25);
}

TEST_CASE("Rsqrt") {
    RsqrtGenerateAssertions();
}

/*
// WARNING: 2^32 iterations -- takes a while!
TEST_CASE("Rsqrt bounds") {
    // Test 1..2^32-1
    #pragma omp parallel for default(none)
    for (int i = 0; i < 0x100; i++) {
        for (uint32_t j = (i > 0) ? 0 : 1; j <= 0x100'0000; j++) {
            auto val = (uint32_t) (i << 24 | j);

            auto N = Log2floor(val);
            auto Y = 4096.0 / sqrt(val / 4096.0);

            constexpr auto F = 12;
            auto M_lb = (3 * F - N - 1) / 2;
            auto M_ub = (3 * F - N + 1) / 2;

            if (M_ub - M_lb > 1 || pow(2.0f, M_lb) > Y || pow(2.0f, M_ub) < Y) {
                printf("val=%10u, Y=%10.3f, log2(Y)=%5.3f, N=%2d, M_lb=%2d, M_ub=%2d\n", val, Y, log2(Y), N, M_lb, M_ub);
            }

            CHECK_LE(M_ub - M_lb, 1);
            CHECK_LE(pow(2.0f, M_lb), Y);
            CHECK_GE(pow(2.0f, M_ub), Y);
        }
    }
}
*/
