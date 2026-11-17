# Checksums and CRCs

COMP 211 Checkoff 3 | Jibran Adil

This demo compares a simple XOR checksum with a two-bit cyclic redundancy check (CRC). Both checks use the same four data bits and the same two simulated bit flips.

## The example

The sender starts with `1001`. For the XOR checksum, it splits the data into `10` and `01` and XORs the chunks to get `11`. After the rightmost bit in each chunk flips, the receiver gets `11` and `00`. Their XOR is still `11` because the two flips cancel in the same column.

For the CRC, the sender appends two temporary zeros to `1001` and XOR-divides `100100` by the generator `111`. The remainder is `00`, so the transmitted CRC packet is `100100`. The same two data flips change it to `110000`. The receiver XOR-divides the entire received packet, including the attached CRC, and gets a nonzero remainder of `01`.

| Case | Data | CRC packet | XOR checksum | CRC remainder |
| --- | --- | --- | --- | --- |
| Intact | `1001` | `100100` | `11` (no error detected) | `00` (no error detected) |
| Two data bits flipped | `1100` | `110000` | `11` (error missed) | `01` (error detected) |

The XOR checksum misses this pair of flips. The CRC catches it because the flips occur at different positions in the full packet and leave a nonzero remainder for this generator.

## Build and run

From the repository folder with GCC installed:

```sh
gcc -std=c11 -Wall -Wextra -pedantic demo.c -o demo
./demo
```

In Windows PowerShell, run `./demo.exe` after compiling. The demo prints the values in binary, including leading zeros.

## References

- [Barr Group, CRC Series, Part 3: CRC Implementation Code in C/C++](https://barrgroup.com/blog/crc-series-part-3-crc-implementation-code-cc) explains bit-by-bit CRC implementation in C and shows how a lookup-table version speeds it up.
- [Computerphile, Cyclic Redundancy Check (CRC)](https://www.youtube.com/watch?v=_x0vbnUKYSU) gives a conceptual overview of CRCs.
