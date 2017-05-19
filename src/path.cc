
#include <iostream>

#include "path.hh"

Path::Path(string ss)
{
    int nn = ss.size();
    int ii = 0;
    int jj = 0;

    while (ii < nn) {
        while (ss[ii] == '/') {
            ii++;
        }

        jj = ii + 1;

        while (jj < nn && ss[jj] != '/') {
            jj++;
        }

        if (jj - ii > 0) {
            parts.push_back(ss.substr(ii, jj - ii));
        }
    }
}

Path
Path::join(string ss)
{
    Path xx(ss);
    return this->join(xx);
}

Path
Path::join(Path pp)
{
    Path yy = *this;

    for (uint ii = 0; ii < pp.parts.size(); ++ii) {
        yy.parts.push_back(pp.parts[ii]);
    }

    return yy;
}

string
Path::to_s()
{
    string ss;

    for (uint ii = 0; ii < parts.size(); ++ii) {
        ss = ss + "/";
        ss = ss + parts[ii];
    }

    return ss;
}

Path
Path::dir()
{
    Path yy = *this;
    if (yy.parts.size() > 0) {
        yy.parts.pop_back();
    }
    return yy;
}

string
Path::base()
{
    int nn = parts.size();
    if (nn > 0) {
        return parts[nn-1];
    }
    else {
        return string("");
    }
}

void
Path::mkdir_p()
{
    std::cout << "Would mkdir: " << to_s() << std::endl;
}
