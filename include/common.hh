#ifndef FOGFS_COMMON_HH
#define FOGFS_COMMON_HH

typedef unsigned int uint;

#include <errno.h>
#include <cstdint>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <thread>
using std::thread;

#include <mutex>
using std::mutex;
using std::lock_guard;

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

#include <array>
typedef std::array<uint8_t, 32> ItemID;
typedef std::array<uint8_t, 32> Hash;

#endif
