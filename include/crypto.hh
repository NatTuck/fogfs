#ifndef FOGFS_CRYPTO_HH
#define FOGFS_CRYPTO_HH

#include <array>

#include "common.hh"

std::array<uint8_t, 32> random_256b();
std::array<uint8_t, 32> hex_to_bin256(string hex);
string bin256_to_hex(std::array<uint8_t, 32> bin);

#endif
