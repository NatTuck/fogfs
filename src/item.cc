
#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <cmath>

#include "item.hh"
#include "errors.hh"
#include "crypto.hh"
#include "settings.hh"
#include "dir.hh"

shared_ptr<Item>
Item::make(uint32_t mode)
{
    switch (mode & S_IFMT) {
    case S_IFREG:
        return make_shared<Item>(mode);
    case S_IFDIR:
        return make_shared<Dir>(mode);
    case S_IFLNK:
        // fall through
    default:
        throw ErrNo(ENOTSUP);
    }
}

Item::Item(uint32_t mode)
{
    this->meta.item_id = random_256b();
    this->meta.mode = mode;
    this->dirty = true;
}

Item::~Item()
{
    lock_guard<mutex> guard(lock);

    if (data) {
        // TODO: munmap
    }
}

static
struct timespec
us2ts(int64_t us)
{
    struct timespec ts;
    ts.tv_sec  = us / 1000000;
    ts.tv_nsec = 1000 * (us % 1000000);
    return ts;
}

struct stat
Item::get_stat()
{
    lock_guard<mutex> guard(lock);

    struct stat st;
    memset(&st, 0, sizeof(st));

    st.st_mode   = meta.mode;
    st.st_nlink  = meta.nlink;
    st.st_size   = meta.size;
    st.st_blocks = (blkcnt_t) ceil(meta.size / 512.0);

    st.st_uid   = getuid();
    st.st_gid   = getgid();

    struct timespec tm = us2ts(meta.mtime_us);
    st.st_atim = tm;
    st.st_mtim = tm;
    st.st_ctim = tm;

    return st;
}

static
int64_t
ts2us(struct timespec ts)
{
    return ts.tv_nsec / 1000 + 1000000 * ts.tv_sec;
}

int
Item::set_time(struct timespec ts)
{
    lock_guard<mutex> guard(lock);

    meta.mtime_us = ts2us(ts);
    dirty = true;
    return 0;
}

