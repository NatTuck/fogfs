
#include <sodium.h>

#include "crypto.hh"

std::array<uint8_t, 32>
random_256b()
{
    std::array<uint8_t, 32> bytes;
    randombytes_buf(bytes.data(), 32);
    return bytes;
}

std::array<uint8_t, 32>
hex_to_bin256(string hex)
{
    std::array<uint8_t, 32> bytes;
    size_t count;
    sodium_hex2bin(bytes.data(), 32, hex.data(), 64, 0, &count, 0);
    return bytes;
}

string
bin256_to_hex(std::array<uint8_t, 32> bin)
{
    char text[72];
    sodium_bin2hex(text, 68, bin.data(), 32);
    return string(text);
}


