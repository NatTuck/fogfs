
#include <errno.h>
#include <string.h>
#include <iostream>

#include "errors.hh"

ErrNo::ErrNo(int err)
    : num(err), msg("")
{
    char tmp[80];
    const char* text = strerror_r(num, tmp, 80);
    msg = msg + string(text);
}

const char*
ErrNo::what() const noexcept
{
    return msg.c_str();
}

string
ErrNo::to_s() const
{
    return msg;
}

int
ErrNo::code() const
{
    return num;
}
