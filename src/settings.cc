#include <sys/types.h>
#include <unistd.h>

#include <basedir.h>

#include "settings.hh"

static mutex lock;
xdgHandle*   xdg = 0;

static
void
settings_init()
{
    if (xdg) {
        return;
    }

    xdgInitHandle(xdg);
}

static
string
pid_as_string()
{
    char  tmp[16];
    pid_t pid = getpid();
    snprintf(tmp, 16, "%d", pid);
    return string(tmp);
}

Path
fogfs_data_path()
{
    lock_guard<mutex> guard(lock);
    settings_init();

    Path base(xdgDataHome(xdg));
    Path data = base.join("fogfs/data");
    data.mkdir_p();
    return data;
}

Path
fogfs_conf_path()
{
    lock_guard<mutex> guard(lock);
    settings_init();

    Path base(xdgConfigHome(xdg));
    base.mkdir_p();
    Path conf = base.join("fogfs.toml");
    return conf;
}

Path
fogfs_cache_base_path()
{
    lock_guard<mutex> guard(lock);
    settings_init();

    Path base(xdgCacheHome(xdg));
    Path cache = base.join("fogfs").join(pid_as_string());
    cache.mkdir_p();
    return cache;
}

Path
fogfs_cache_path()
{
    return fogfs_cache_base_path().join(pid_as_string());
}



