
#include "cache.hh"

static mutex lock;
static map<string, shared_ptr<Item>> items;

bool
cache_exists(string path)
{
    auto item = cache_get(path);
    return bool(item);
}

shared_ptr<Item>
cache_get(string path)
{
    lock_guard<mutex> guard(lock);
    auto item_it = items.find(path);
    if (item_it != items.end()) {
        return item_it->second;
    }
    else {
        return shared_ptr<Item>();
    }
}

shared_ptr<Item>
cache_create(string path, mode_t mode)
{
    lock_guard<mutex> guard(lock);

    return shared_ptr<Item>();
}

