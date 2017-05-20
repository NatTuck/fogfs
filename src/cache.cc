
#include <iostream>

#include "errors.hh"
#include "crypto.hh"
#include "common.hh"
#include "cache.hh"
#include "dir.hh"

static mutex lock;
static map<string, ItemID> paths;
static map<ItemID, shared_ptr<Item>> items;

void
cache_init()
{
    lock_guard<mutex> guard(lock);
    if (!cache_exists_nolock("/")) {
        auto root = Item::make(040755);
        root->meta.nlink = 1;

        auto item_id = root->meta.item_id;
        items[item_id] = root;
        paths[string("/")] = item_id;

        std::cout << "Created root ["
                  << bin256_to_hex(item_id)
                  << "]" << std::endl;
    }
}

bool
cache_exists(string path)
{
    lock_guard<mutex> guard(lock);
    return cache_exists_nolock(path);
}

bool
cache_exists_nolock(string path)
{
    shared_ptr<Item> item;
    try {
        item = cache_get_path_nolock(path);
    }
    catch (ErrNo& _ee) {
        // do nothing
    }
    return bool(item);
}

shared_ptr<Item>
cache_get_path(string path)
{
    lock_guard<mutex> guard(lock);
    return cache_get_path_nolock(path);
}

shared_ptr<Item>
cache_get_id(ItemID item_id)
{
    lock_guard<mutex> guard(lock);
    return cache_get_id_nolock(item_id);
}

shared_ptr<Item>
cache_get_path_nolock(string path)
{
    try {
        auto item_id = paths.at(path);
        return cache_get_id_nolock(item_id);
    }
    catch (std::out_of_range& ee) {
        throw ErrNo(ENOENT);
    }
}

shared_ptr<Item>
cache_get_id_nolock(ItemID item_id)
{
    try {
        return items[item_id];
    }
    catch (std::out_of_range& ee) {
        throw ErrNo(ENOENT);
    }
}

void
cache_create(string path, mode_t mode)
{
    lock_guard<mutex> guard(lock);
    cache_create_nolock(path, mode);
}

void
cache_create_nolock(string path, mode_t mode)
{
    if (cache_exists_nolock(path)) {
        throw ErrNo(EEXIST);
    }

    string ppath = Path(path).dir().to_s();

    if (!cache_exists_nolock(ppath)) {
        std::cout << "Parent " << ppath << " doesn't exist." << std::endl;
        throw ErrNo(ENOENT);
    }

    auto pitem = cache_get_path_nolock(ppath);
    std::cout << "create("
              << path
              << "), parent = "
              << bin256_to_hex(pitem->meta.item_id)
              << std::endl;

    auto pdir  = dynamic_pointer_cast<Dir>(pitem);
    if (!pdir) {
        throw ErrNo(ENOTDIR);
    }

    auto item = Item::make(mode);
    item->meta.nlink = 1;

    auto item_id = item->meta.item_id;
    items[item_id] = item;
    paths[path] = item_id;

    pdir->put(Path(path).base(), item_id);

    std::cout << "Created item ["
              << bin256_to_hex(item_id)
              << "] at path: "
              << path << std::endl;
}

