#ifndef FOGFS_CACHE_HH
#define FOGFS_CACHE_HH

#include "common.hh"
#include "item.hh"
#include "path.hh"

bool             cache_exists(string path);
shared_ptr<Item> cache_get(string path);
shared_ptr<Item> cache_create(string path, mode_t mode);

#endif
