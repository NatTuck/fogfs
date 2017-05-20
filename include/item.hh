#ifndef FOGFS_ITEM_HH
#define FOGFS_ITEM_HH

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>

#include "common.hh"

struct ItemMeta {
    // Should be 56 bytes.
    ItemID   item_id;
    uint32_t mode;
    uint32_t nlink;
    int64_t  size;
    int64_t  mtime_us; // UNIX time microseconds
};

class Item {
  public:
    static shared_ptr<Item> make(uint32_t mode);

    Item(uint32_t mode);
    virtual ~Item();

    mutex    lock;

    ItemMeta meta;
    bool     dirty;

    void*    data; // mmaped temp file

    // 4k pages
    vector<bool> cache_pages;
    vector<bool> dirty_pages;

    // Generic methods
    bool is_dir() { return S_ISDIR(meta.mode); }
    bool is_reg() { return S_ISREG(meta.mode); }
    bool is_lnk() { return S_ISLNK(meta.mode); }

    struct stat get_stat();
    int set_time(struct timespec ts);
};

#endif

