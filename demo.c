#include <stdio.h>

/* XOR the two 2-bit chunks of a 4-bit message. */
static unsigned xor_checksum(unsigned data)
{
    return (data >> 2) ^ (data & 3u);
}

/* XOR-divide a 6-bit packet by binary 111. */
static unsigned crc_remainder(unsigned bits)
{
    const unsigned generator = 7u;

    for (int i = 5; i >= 2; --i) {
        if ((bits >> i) & 1u) {
            bits ^= generator << (i - 2);
        }
    }

    return bits & 3u;
}

static void print_bits(unsigned bits, int width)
{
    for (int i = width - 1; i >= 0; --i) {
        putchar(((bits >> i) & 1u) ? '1' : '0');
    }
}

static void show_result(const char *label, unsigned packet,
                        unsigned sent_checksum)
{
    unsigned data = packet >> 2;
    unsigned checksum = xor_checksum(data);
    unsigned remainder = crc_remainder(packet);

    printf("%s\n  Data: ", label);
    print_bits(data, 4);
    printf("\n  CRC packet: ");
    print_bits(packet, 6);
    printf("\n  XOR checksum: ");
    print_bits(checksum, 2);
    printf(" (%s)\n  CRC remainder: ",
           checksum == sent_checksum ? "no error detected" : "error detected");
    print_bits(remainder, 2);
    printf(" (%s)\n", remainder == 0u ? "no error detected" : "error detected");
}

int main(void)
{
    const unsigned data = 9u; /* Binary 1001 */
    const unsigned flip_mask = 20u; /* Binary 010100 */
    const unsigned sent_checksum = xor_checksum(data);
    const unsigned padded_data = data << 2;
    const unsigned crc = crc_remainder(padded_data);
    const unsigned packet = padded_data | crc;

    printf("Sender's XOR checksum: ");
    print_bits(sent_checksum, 2);
    printf("\nSender's attached CRC: ");
    print_bits(crc, 2);
    printf("\n\n");

    show_result("Intact transmission", packet, sent_checksum);
    putchar('\n');
    show_result("After two data bits flip", packet ^ flip_mask, sent_checksum);
    return 0;
}
