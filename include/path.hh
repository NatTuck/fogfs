#ifndef FOGFS_PATH_HH
#define FOGFS_PATH_HH

#include "common.hh"

class Path {
  public:
    vector<string> parts;

    Path(string ss);

    Path   join(string ss);
    Path   join(Path pp);

    string to_s();
    Path   dir();
    string base();

    void   mkdir_p();
};

#endif
