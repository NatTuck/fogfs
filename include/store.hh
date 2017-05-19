#include "common.hh"

namespace fogfs {

class Journal {
  public:
    string name;
    size_t size;
    void*  data;
};

class Store {
  public:
    string path;
    map<string, Journal> journals;

    static Store* get();

  private:
    Store* instance;

    Store();
};

};
