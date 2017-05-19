#ifndef FOGFS_ITEM_HH
#define FOGFS_ITEM_HH

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>

#include "common.hh"

typedef std::array<uint8_t, 16> ItemID;

struct ItemMeta {
    // Should be 40 bytes.
    ItemID   item_id;
    uint32_t mode;
    uint32_t nlink;
    int64_t  size;
    int64_t  mtime_us; // UNIX time microseconds
};

class Item {
  public:
    Item();
    ~Item();

    mutex    lock;

    ItemMeta meta;
    bool     dirty;

    void*    data; // mmaped temp file

    // 4k pages
    vector<bool> cache_pages;
    vector<bool> dirty_pages;

    // Methods
    struct stat get_stat();
    int set_time(struct timespec ts);
};

#endif

