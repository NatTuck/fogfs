#ifndef FOGFS_ERRORS_HH
#define FOGFS_ERRORS_HH

#include <exception>

#include "common.hh"

class ErrNo : public std::exception {
  public:
    ErrNo(int err);

    const char*  what() const noexcept;
    string       to_s() const;
    int          code() const;

  protected:
    int    num;
    string msg;
};

#endif
