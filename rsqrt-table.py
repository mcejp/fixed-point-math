#!/usr/bin/env python3

import math

FRAC_BITS = 12
ENTRIES_PER_LINE = 8

for table_bits in [5, 6, 7, 8]:
    table_size = 2**table_bits + 1

    print(f"#if RSQRT_TABLE_BITS == {table_bits}")
    print(f"const uint16_t rsqrt_table[{table_size}] = {{")

    for i in range(table_size):
        if i % ENTRIES_PER_LINE == 0:
            print("    ", end="")
        else:
            print(" ", end="")

        # 0 => 2*16
        # len => 2**18

        if i == 0:
            rsqrt = 2**FRAC_BITS - 1
        else:
            rsqrt = round(2**FRAC_BITS / math.sqrt(i / (table_size - 1) * 4))

        print(f"0x{rsqrt:04x},", end="")

        if (i + 1) % ENTRIES_PER_LINE == 0 or i + 1 == table_size:
            print("\n", end="")

    print("};")
    print("#endif")
    print()
