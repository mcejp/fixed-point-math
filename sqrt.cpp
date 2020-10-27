#include "sqrt.hpp"

#include <doctest.h>
#include <math.h>
#include <stdio.h>

// TODO: quantify required/achieved absolute/relative tolerance

// Using 8.24 input, 20.12 output
// Maximum input: 256.0 - epsilon
static void SqrtDemo1(double number) {
    if (number * 16777216.0 > UINT32_MAX) {
        return;
    }

    int num_iterations;
    int input_int = (int)(number * 16777216.0);
    int eval = Sqrtu(input_int, &num_iterations);

    double correct_result = sqrt(number * 16777216.0);
    int correct_eval = (int)round(correct_result);

    double error = (eval != correct_eval) ? (double)(eval - correct_result) / correct_result : 0;

    if (abs(error) > 1) {
        error = NAN;
    }

    // Uncomment this to print out a lot of info
//    printf("sqrt(%14.2f) -> %12.3f vs %9.3f, %+7.2f%% error // (%10u) -> %12d vs %12d [%+12d after %2d iterations]\n",
//           number, eval / 4096.0, correct_result / 4096.0, error * 100,
//           (unsigned int)(number * 16777216.0), eval, correct_eval,
//           eval - correct_eval, num_iterations);
    // Uncomment this to generate test assertions
    printf("CHECK_LE(abs((int) Sqrtu(%10d) - (int) round(sqrt(%10d))), %3d);\n", input_int, input_int,
           1 + correct_eval / 100);
}

static void SqrtTest2(uint32_t value, double* rel_error_out, int* abs_error_out, int* num_iterations_out) {
    int eval = Sqrtu(value, num_iterations_out);

    double correct_result = sqrt(value);
    int correct_eval = (int)round(correct_result);
    *rel_error_out = (eval != correct_eval) ? (double)(eval - correct_result) / correct_result : 0;
    *abs_error_out = eval - correct_eval;
}

static void SqrtGenerateAssertions() {
    for (int i = 0; i < 20; i++) {
        SqrtDemo1(i * 0.2);
    }

    for (int i = 1; i < 3; i++) {
        SqrtDemo1(pow(10, i));
    }

    SqrtDemo1(1 / 16777216.0);
    SqrtDemo1(2 / 16777216.0);
    SqrtDemo1(3 / 16777216.0);
    SqrtDemo1(4 / 16777216.0);
    SqrtDemo1(0.25);
}

static void SqrtTestRange() {
    int max_abs_error = 0;
    int max_abs_error_value;
    double max_rel_error = 0;
    int max_rel_error_value;
    int max_num_iterations = 0;
    int max_num_iterations_value;

    for (int i = 0; i < 0x01000000; i++) {
        double error;
        int abs_error;
        int num_iterations;

        SqrtTest2(i, &error, &abs_error, &num_iterations);

        if (abs_error > max_abs_error) {
            max_abs_error = abs_error;
            max_abs_error_value = i;
        }

        if (i > 1000 && error > max_rel_error) {
            max_rel_error = error;
            max_rel_error_value = i;
        }

        if (num_iterations > max_num_iterations) {
            max_num_iterations = num_iterations;
            max_num_iterations_value = i;
        }
    }

    printf("MAX ABS ERROR:  %d aka %.10f for value %d aka %.10f\n", max_abs_error, max_abs_error / 16777216.0, max_abs_error_value, max_abs_error_value / 16777216.0);
    printf("MAX REL ERROR:  %+7.2f%% for value %d aka %.10f\n", max_rel_error * 100, max_rel_error_value, max_rel_error_value / 16777216.0);
    printf("MAX ITERATIONS: %d for value %d aka %.10f\n", max_num_iterations, max_num_iterations_value, max_num_iterations_value / 16777216.0);
}

TEST_CASE("Sqrtu") {
//    SqrtGenerateAssertions();
//    SqrtTestRange();

    CHECK_LE(abs((int) Sqrtu(         0) - (int) round(sqrt(         0))),   1);
    CHECK_LE(abs((int) Sqrtu(   3355443) - (int) round(sqrt(   3355443))),  19);
    CHECK_LE(abs((int) Sqrtu(   6710886) - (int) round(sqrt(   6710886))),  26);
    CHECK_LE(abs((int) Sqrtu(  10066329) - (int) round(sqrt(  10066329))),  32);
    CHECK_LE(abs((int) Sqrtu(  13421772) - (int) round(sqrt(  13421772))),  37);
    CHECK_LE(abs((int) Sqrtu(  16777216) - (int) round(sqrt(  16777216))),  41);
    CHECK_LE(abs((int) Sqrtu(  20132659) - (int) round(sqrt(  20132659))),  45);
    CHECK_LE(abs((int) Sqrtu(  23488102) - (int) round(sqrt(  23488102))),  49);
    CHECK_LE(abs((int) Sqrtu(  26843545) - (int) round(sqrt(  26843545))),  52);
    CHECK_LE(abs((int) Sqrtu(  30198988) - (int) round(sqrt(  30198988))),  55);
    CHECK_LE(abs((int) Sqrtu(  33554432) - (int) round(sqrt(  33554432))),  58);
    CHECK_LE(abs((int) Sqrtu(  36909875) - (int) round(sqrt(  36909875))),  61);
    CHECK_LE(abs((int) Sqrtu(  40265318) - (int) round(sqrt(  40265318))),  64);
    CHECK_LE(abs((int) Sqrtu(  43620761) - (int) round(sqrt(  43620761))),  67);
    CHECK_LE(abs((int) Sqrtu(  46976204) - (int) round(sqrt(  46976204))),  69);
    CHECK_LE(abs((int) Sqrtu(  50331648) - (int) round(sqrt(  50331648))),  71);
    CHECK_LE(abs((int) Sqrtu(  53687091) - (int) round(sqrt(  53687091))),  74);
    CHECK_LE(abs((int) Sqrtu(  57042534) - (int) round(sqrt(  57042534))),  76);
    CHECK_LE(abs((int) Sqrtu(  60397977) - (int) round(sqrt(  60397977))),  78);
    CHECK_LE(abs((int) Sqrtu(  63753420) - (int) round(sqrt(  63753420))),  80);
    CHECK_LE(abs((int) Sqrtu( 167772160) - (int) round(sqrt( 167772160))), 130);
    CHECK_LE(abs((int) Sqrtu(1677721600) - (int) round(sqrt(1677721600))), 410);
    CHECK_LE(abs((int) Sqrtu(         1) - (int) round(sqrt(         1))),   1);
    CHECK_LE(abs((int) Sqrtu(         2) - (int) round(sqrt(         2))),   1);
    CHECK_LE(abs((int) Sqrtu(         3) - (int) round(sqrt(         3))),   1);
    CHECK_LE(abs((int) Sqrtu(         4) - (int) round(sqrt(         4))),   1);
    CHECK_LE(abs((int) Sqrtu(   4194304) - (int) round(sqrt(   4194304))),  21);
}
