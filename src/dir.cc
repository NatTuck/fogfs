
#include "dir.hh"

Dir::Dir(uint32_t mode)
    : Item(mode)
{
    // do nothing
}

void
Dir::put(string name, ItemID item_id)
{
    ents[name] = item_id;
}

ItemID
Dir::get(string name)
{
    return ents[name];
}

vector<DirEnt>
Dir::list()
{
    vector<DirEnt> ys;
    for (auto it = ents.begin(); it != ents.end(); ++it) {
        DirEnt yy;
        yy.name    = it->first;
        yy.item_id = it->second;
        ys.push_back(yy);
    }
    return ys;
}
