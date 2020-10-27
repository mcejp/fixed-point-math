#include "sin_cos.hpp"

#include <doctest.h>

#include <math.h>
#include <stdio.h>

#if SIN_TABLE_BITS == 5
const uint16_t sin_table[33] = {
    0x0000, 0x00c9, 0x0191, 0x0259, 0x031f, 0x03e3, 0x04a5, 0x0564,
    0x061f, 0x06d7, 0x078b, 0x083a, 0x08e4, 0x0988, 0x0a26, 0x0abf,
    0x0b50, 0x0bdb, 0x0c5e, 0x0cda, 0x0d4e, 0x0db9, 0x0e1c, 0x0e77,
    0x0ec8, 0x0f11, 0x0f50, 0x0f85, 0x0fb1, 0x0fd4, 0x0fec, 0x0ffb,
    0x1000,
};
#endif

#if SIN_TABLE_BITS == 6
const uint16_t sin_table[65] = {
    0x0000, 0x0065, 0x00c9, 0x012d, 0x0191, 0x01f5, 0x0259, 0x02bc,
    0x031f, 0x0381, 0x03e3, 0x0444, 0x04a5, 0x0505, 0x0564, 0x05c2,
    0x061f, 0x067c, 0x06d7, 0x0732, 0x078b, 0x07e3, 0x083a, 0x088f,
    0x08e4, 0x0937, 0x0988, 0x09d8, 0x0a26, 0x0a73, 0x0abf, 0x0b08,
    0x0b50, 0x0b97, 0x0bdb, 0x0c1e, 0x0c5e, 0x0c9d, 0x0cda, 0x0d15,
    0x0d4e, 0x0d85, 0x0db9, 0x0dec, 0x0e1c, 0x0e4b, 0x0e77, 0x0ea1,
    0x0ec8, 0x0eee, 0x0f11, 0x0f31, 0x0f50, 0x0f6c, 0x0f85, 0x0f9c,
    0x0fb1, 0x0fc4, 0x0fd4, 0x0fe1, 0x0fec, 0x0ff5, 0x0ffb, 0x0fff,
    0x1000,
};
#endif

#if SIN_TABLE_BITS == 7
const uint16_t sin_table[129] = {
    0x0000, 0x0032, 0x0065, 0x0097, 0x00c9, 0x00fb, 0x012d, 0x015f,
    0x0191, 0x01c3, 0x01f5, 0x0227, 0x0259, 0x028b, 0x02bc, 0x02ee,
    0x031f, 0x0350, 0x0381, 0x03b2, 0x03e3, 0x0414, 0x0444, 0x0475,
    0x04a5, 0x04d5, 0x0505, 0x0534, 0x0564, 0x0593, 0x05c2, 0x05f1,
    0x061f, 0x064e, 0x067c, 0x06aa, 0x06d7, 0x0705, 0x0732, 0x075e,
    0x078b, 0x07b7, 0x07e3, 0x080e, 0x083a, 0x0865, 0x088f, 0x08ba,
    0x08e4, 0x090d, 0x0937, 0x095f, 0x0988, 0x09b0, 0x09d8, 0x09ff,
    0x0a26, 0x0a4d, 0x0a73, 0x0a99, 0x0abf, 0x0ae4, 0x0b08, 0x0b2d,
    0x0b50, 0x0b74, 0x0b97, 0x0bb9, 0x0bdb, 0x0bfc, 0x0c1e, 0x0c3e,
    0x0c5e, 0x0c7e, 0x0c9d, 0x0cbc, 0x0cda, 0x0cf8, 0x0d15, 0x0d32,
    0x0d4e, 0x0d69, 0x0d85, 0x0d9f, 0x0db9, 0x0dd3, 0x0dec, 0x0e04,
    0x0e1c, 0x0e34, 0x0e4b, 0x0e61, 0x0e77, 0x0e8c, 0x0ea1, 0x0eb5,
    0x0ec8, 0x0edb, 0x0eee, 0x0eff, 0x0f11, 0x0f21, 0x0f31, 0x0f41,
    0x0f50, 0x0f5e, 0x0f6c, 0x0f79, 0x0f85, 0x0f91, 0x0f9c, 0x0fa7,
    0x0fb1, 0x0fbb, 0x0fc4, 0x0fcc, 0x0fd4, 0x0fdb, 0x0fe1, 0x0fe7,
    0x0fec, 0x0ff1, 0x0ff5, 0x0ff8, 0x0ffb, 0x0ffd, 0x0fff, 0x1000,
    0x1000,
};
#endif

static void DemoSin(int32_t i) {
    auto got = Sin<12, int32_t>(i);
    auto exp = Sin<12, int32_t>(i * M_PI / 2048.0f) * 4096.0f;
//    printf("Sin<12, int32_t>(%4d) = %5d (vs %7.2f)\n", i, got, exp);
    printf("CHECK_EQ(Sin<12, int32_t>(%4d), %5d);\n", i, got);
}

TEST_CASE("Sin<12, int32_t>(int32_t)") {
    CHECK_EQ(Sin<12, int32_t>(   0),     0);
    CHECK_EQ(Sin<12, int32_t>(   1),     6);
    CHECK_EQ(Sin<12, int32_t>(   2),    13);
    CHECK_EQ(Sin<12, int32_t>(   3),    19);
    CHECK_EQ(Sin<12, int32_t>(   4),    25);
    CHECK_EQ(Sin<12, int32_t>(   5),    32);
    CHECK_EQ(Sin<12, int32_t>(   6),    38);
    CHECK_EQ(Sin<12, int32_t>(   7),    44);
    CHECK_EQ(Sin<12, int32_t>(   8),    51);
    CHECK_EQ(Sin<12, int32_t>(   9),    57);
    CHECK_EQ(Sin<12, int32_t>(  10),    63);
    CHECK_EQ(Sin<12, int32_t>(  11),    69);
    CHECK_EQ(Sin<12, int32_t>(  12),    76);
    CHECK_EQ(Sin<12, int32_t>(  13),    82);
    CHECK_EQ(Sin<12, int32_t>(  14),    88);
    CHECK_EQ(Sin<12, int32_t>(  15),    95);
    CHECK_EQ(Sin<12, int32_t>(  16),   101);
    CHECK_EQ(Sin<12, int32_t>(1013),  4095);
    CHECK_EQ(Sin<12, int32_t>(1014),  4095);
    CHECK_EQ(Sin<12, int32_t>(1015),  4095);
    CHECK_EQ(Sin<12, int32_t>(1016),  4096);
    CHECK_EQ(Sin<12, int32_t>(1017),  4096);
    CHECK_EQ(Sin<12, int32_t>(1018),  4096);
    CHECK_EQ(Sin<12, int32_t>(1019),  4096);
    CHECK_EQ(Sin<12, int32_t>(1020),  4096);
    CHECK_EQ(Sin<12, int32_t>(1021),  4096);
    CHECK_EQ(Sin<12, int32_t>(1022),  4096);
    CHECK_EQ(Sin<12, int32_t>(1023),  4096);
    CHECK_EQ(Sin<12, int32_t>(1024),  4096);
    CHECK_EQ(Sin<12, int32_t>(1025),  4096);
    CHECK_EQ(Sin<12, int32_t>(1026),  4096);
    CHECK_EQ(Sin<12, int32_t>(1027),  4096);
    CHECK_EQ(Sin<12, int32_t>(2044),    25);
    CHECK_EQ(Sin<12, int32_t>(2045),    19);
    CHECK_EQ(Sin<12, int32_t>(2046),    13);
    CHECK_EQ(Sin<12, int32_t>(2047),     6);
    CHECK_EQ(Sin<12, int32_t>(2048),     0);
    CHECK_EQ(Sin<12, int32_t>(2049),    -6);
    CHECK_EQ(Sin<12, int32_t>(2050),   -13);
    CHECK_EQ(Sin<12, int32_t>(2051),   -19);
    CHECK_EQ(Sin<12, int32_t>(3068), -4096);
    CHECK_EQ(Sin<12, int32_t>(3069), -4096);
    CHECK_EQ(Sin<12, int32_t>(3070), -4096);
    CHECK_EQ(Sin<12, int32_t>(3071), -4096);
    CHECK_EQ(Sin<12, int32_t>(3072), -4096);
    CHECK_EQ(Sin<12, int32_t>(3073), -4096);
    CHECK_EQ(Sin<12, int32_t>(3074), -4096);
    CHECK_EQ(Sin<12, int32_t>(3075), -4096);
    CHECK_EQ(Sin<12, int32_t>(4092),   -25);
    CHECK_EQ(Sin<12, int32_t>(4093),   -19);
    CHECK_EQ(Sin<12, int32_t>(4094),   -13);
    CHECK_EQ(Sin<12, int32_t>(4095),    -6);
    CHECK_EQ(Sin<12, int32_t>(4096),     0);
    CHECK_EQ(Sin<12, int32_t>(4097),     6);
    CHECK_EQ(Sin<12, int32_t>(4098),    13);
    CHECK_EQ(Sin<12, int32_t>(4099),    19);

    /*
    for (int i = 0; i <= 16; i++) {
        DemoSin<12, int32_t>(i);
    }

    for (int i = 1013; i < 1028; i++) {
        DemoSin<12, int32_t>(i);
    }

    for (int i = 2044; i < 2052; i++) {
        DemoSin<12, int32_t>(i);
    }

    for (int i = 3068; i < 3076; i++) {
        DemoSin<12, int32_t>(i);
    }

    for (int i = 4092; i < 4100; i++) {
        DemoSin<12, int32_t>(i);
    }
    */
    /*
    float total_error = 0.0f;
    float total_bias = 0.0f;
    float max_error = 0.0f;

    for (int i = 0; i < 4096; i++) {
        auto get = Sin<12, int32_t>(i);
        auto exp = Sin<12, int32_t>(i * M_PI / 2048.0f) * 4096.0f;

        total_bias += get - exp;
        total_error += fabs(get - exp);
        max_error = Max2<float>(max_error, fabs(get - exp));
    }
    printf("TOTAL ERROR: %f\tTOTAL BIAS: %f\tMAX ERROR: %f\n", total_error, total_bias, max_error);
    */
}

static void DemoCos(int32_t i) {
    auto got = Cos<12, int32_t>(i);
    auto exp = Cos<12, int32_t>(i * M_PI / 2048.0f) * 4096.0f;
//    printf("Cos<12, int32_t>(%4d) = %5d (vs %7.2f)\n", i, got, exp);
    printf("CHECK_EQ(Cos<12, int32_t>(%4d), %5d);\n", i, got);
}

TEST_CASE("Cos<12, int32_t>(int32_t)") {
    CHECK_EQ(Cos<12, int32_t>(   0),  4096);
    CHECK_EQ(Cos<12, int32_t>(   1),  4096);
    CHECK_EQ(Cos<12, int32_t>(   2),  4096);
    CHECK_EQ(Cos<12, int32_t>(   3),  4096);
    CHECK_EQ(Cos<12, int32_t>(   4),  4096);
    CHECK_EQ(Cos<12, int32_t>(   5),  4096);
    CHECK_EQ(Cos<12, int32_t>(   6),  4096);
    CHECK_EQ(Cos<12, int32_t>(   7),  4096);
    CHECK_EQ(Cos<12, int32_t>(   8),  4096);
    CHECK_EQ(Cos<12, int32_t>(   9),  4095);
    CHECK_EQ(Cos<12, int32_t>(  10),  4095);
    CHECK_EQ(Cos<12, int32_t>(  11),  4095);
    CHECK_EQ(Cos<12, int32_t>(  12),  4095);
    CHECK_EQ(Cos<12, int32_t>(  13),  4095);
    CHECK_EQ(Cos<12, int32_t>(  14),  4095);
    CHECK_EQ(Cos<12, int32_t>(  15),  4095);
    CHECK_EQ(Cos<12, int32_t>(  16),  4095);
    CHECK_EQ(Cos<12, int32_t>(1013),    69);
    CHECK_EQ(Cos<12, int32_t>(1014),    63);
    CHECK_EQ(Cos<12, int32_t>(1015),    57);
    CHECK_EQ(Cos<12, int32_t>(1016),    51);
    CHECK_EQ(Cos<12, int32_t>(1017),    44);
    CHECK_EQ(Cos<12, int32_t>(1018),    38);
    CHECK_EQ(Cos<12, int32_t>(1019),    32);
    CHECK_EQ(Cos<12, int32_t>(1020),    25);
    CHECK_EQ(Cos<12, int32_t>(1021),    19);
    CHECK_EQ(Cos<12, int32_t>(1022),    13);
    CHECK_EQ(Cos<12, int32_t>(1023),     6);
    CHECK_EQ(Cos<12, int32_t>(1024),     0);
    CHECK_EQ(Cos<12, int32_t>(1025),    -6);
    CHECK_EQ(Cos<12, int32_t>(1026),   -13);
    CHECK_EQ(Cos<12, int32_t>(1027),   -19);
    CHECK_EQ(Cos<12, int32_t>(2044), -4096);
    CHECK_EQ(Cos<12, int32_t>(2045), -4096);
    CHECK_EQ(Cos<12, int32_t>(2046), -4096);
    CHECK_EQ(Cos<12, int32_t>(2047), -4096);
    CHECK_EQ(Cos<12, int32_t>(2048), -4096);
    CHECK_EQ(Cos<12, int32_t>(2049), -4096);
    CHECK_EQ(Cos<12, int32_t>(2050), -4096);
    CHECK_EQ(Cos<12, int32_t>(2051), -4096);
    CHECK_EQ(Cos<12, int32_t>(3068),   -25);
    CHECK_EQ(Cos<12, int32_t>(3069),   -19);
    CHECK_EQ(Cos<12, int32_t>(3070),   -13);
    CHECK_EQ(Cos<12, int32_t>(3071),    -6);
    CHECK_EQ(Cos<12, int32_t>(3072),     0);
    CHECK_EQ(Cos<12, int32_t>(3073),     6);
    CHECK_EQ(Cos<12, int32_t>(3074),    13);
    CHECK_EQ(Cos<12, int32_t>(3075),    19);
    CHECK_EQ(Cos<12, int32_t>(4092),  4096);
    CHECK_EQ(Cos<12, int32_t>(4093),  4096);
    CHECK_EQ(Cos<12, int32_t>(4094),  4096);
    CHECK_EQ(Cos<12, int32_t>(4095),  4096);
    CHECK_EQ(Cos<12, int32_t>(4096),  4096);
    CHECK_EQ(Cos<12, int32_t>(4097),  4096);
    CHECK_EQ(Cos<12, int32_t>(4098),  4096);
    CHECK_EQ(Cos<12, int32_t>(4099),  4096);

    /*
    for (int i = 0; i <= 16; i++) {
        DemoCos<12, int32_t>(i);
    }

    for (int i = 1013; i < 1028; i++) {
        DemoCos<12, int32_t>(i);
    }

    for (int i = 2044; i < 2052; i++) {
        DemoCos<12, int32_t>(i);
    }

    for (int i = 3068; i < 3076; i++) {
        DemoCos<12, int32_t>(i);
    }

    for (int i = 4092; i < 4100; i++) {
        DemoCos<12, int32_t>(i);
    }
    */
    /*
    float total_error = 0.0f;
    float total_bias = 0.0f;
    float max_error = 0.0f;

    for (int i = 0; i < 4096; i++) {
        auto get = Cos<12, int32_t>(i);
        auto exp = Cos<12, int32_t>(i * M_PI / 2048.0f) * 4096.0f;

        total_bias += get - exp;
        total_error += fabs(get - exp);
        max_error = Max2<float>(max_error, fabs(get - exp));
    }
    printf("TOTAL ERROR: %f\tTOTAL BIAS: %f\tMAX ERROR: %f\n", total_error, total_bias, max_error);
    */
}
