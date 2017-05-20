#ifndef FOGFS_CACHE_HH
#define FOGFS_CACHE_HH

#include "common.hh"
#include "item.hh"
#include "path.hh"

void             cache_init();
bool             cache_exists(string path);
bool             cache_exists_nolock(string path);
shared_ptr<Item> cache_get_path(string path);
shared_ptr<Item> cache_get_path_nolock(string path);
shared_ptr<Item> cache_get_id(ItemID item_id);
shared_ptr<Item> cache_get_id_nolock(ItemID item_id);
void             cache_create(string path, mode_t mode);
void             cache_create_nolock(string path, mode_t mode);

#endif
