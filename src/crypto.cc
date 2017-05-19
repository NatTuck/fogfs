
#include <sodium.h>

#include "crypto.hh"

std::array<uint8_t, 16>
random_128b()
{
    std::array<uint8_t, 16> bytes;
    randombytes_buf(bytes.data(), 16);
    return bytes;
}

