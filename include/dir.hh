#ifndef FOGFS_DIR_HH
#define FOGFS_DIR_HH

#include "common.hh"
#include "item.hh"

struct DirEnt {
    string name;
    ItemID item_id;
};

class Dir : public Item {
  public:
    Dir(uint32_t mode);

    void   put(string name, ItemID item_id);
    ItemID get(string name);
    vector<DirEnt> list();

  private:
    map<string, ItemID> ents;
};

#endif
