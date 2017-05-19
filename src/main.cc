#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <bsd/string.h>
#include <assert.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>

#include "item.hh"
#include "cache.hh"

int
fogfs_init()
{
    printf("Fogfs starting up...\n");
    return 0;
}

int
fogfs_access(const char *path, int mask)
{
    return 0;
}

int
fogfs_getattr(const char *path, struct stat *st)
{
    auto node = cache_get(string(path));


    if (node) {
        *st = node->get_stat();
        printf("getattr(%s) -> 0 {mode: 0%o}\n", path, st->st_mode);
        return 0;
    }
    else {
        printf("getattr(%s) -> -ENOENT\n", path);
        return -ENOENT;
    }
}

int
fogfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
             off_t offset, struct fuse_file_info *fi)
{
    struct stat st;

    printf("readdir(%s)\n", path);

    // filler is a callback that adds one item to the result
    // it will return non-zero when the buffer is full
    st.st_mode = 040755;
    filler(buf, ".", &st, 0);

    //get_stat("/hello.txt", &st);
    //filler(buf, "hello.txt", &st, 0);

    return 0;
}

int
fogfs_mknod(const char *path, mode_t mode, dev_t rdev)
{
    printf("mknod(%s, %04o)\n", path, mode);
    return -1;
}

int
fogfs_mkdir(const char *path, mode_t mode)
{
    printf("mkdir(%s)\n", path);
    return -1;
}

int
fogfs_unlink(const char *path)
{
    printf("unlink(%s)\n", path);
    return -1;
}

int
fogfs_rmdir(const char *path)
{
    printf("rmdir(%s)\n", path);
    return -1;
}

int
fogfs_rename(const char *from, const char *to)
{
    printf("rename(%s => %s)\n", from, to);
    return -1;
}

int
fogfs_chmod(const char *path, mode_t mode)
{
    printf("chmod(%s, %04o)\n", path, mode);
    return -1;
}

int
fogfs_truncate(const char *path, off_t size)
{
    printf("truncate(%s, %ld bytes)\n", path, size);
    return -1;
}

int
fogfs_open(const char *path, struct fuse_file_info *fi)
{
    printf("open(%s)\n", path);
    return 0;
}

int
fogfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("read(%s, %ld bytes, @%ld)\n", path, size, offset);
    const char* data = "the quick brown fox jumps over the lazy dog.\n";

    size_t len = strlen(data) + 1;
    if (size < len) {
        len = size;
    }

    strlcpy(buf, data, len);
    return len;
}

int
fogfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("write(%s, %ld bytes, @%ld)\n", path, size, offset);
    return -1;
}

int
fogfs_utimens(const char* path, const struct timespec ts[2])
{
    int rv = -1; //storage_set_time(path, ts);
    printf("utimens(%s, [%ld, %ld; %ld %ld]) -> %d\n",
           path, ts[0].tv_sec, ts[0].tv_nsec, ts[1].tv_sec, ts[1].tv_nsec, rv);
	return rv;
}

void
fogfs_init_ops(struct fuse_operations* ops)
{
    memset(ops, 0, sizeof(struct fuse_operations));
    ops->access   = fogfs_access;
    ops->getattr  = fogfs_getattr;
    ops->readdir  = fogfs_readdir;
    ops->mknod    = fogfs_mknod;
    ops->mkdir    = fogfs_mkdir;
    ops->unlink   = fogfs_unlink;
    ops->rmdir    = fogfs_rmdir;
    ops->rename   = fogfs_rename;
    ops->chmod    = fogfs_chmod;
    ops->truncate = fogfs_truncate;
    ops->open	  = fogfs_open;
    ops->read     = fogfs_read;
    ops->write    = fogfs_write;
    ops->utimens  = fogfs_utimens;
};

int
main(int argc, char *argv[])
{
    struct fuse_operations fogfs_ops;
    fogfs_init();
    fogfs_init_ops(&fogfs_ops);
    return fuse_main(argc, argv, &fogfs_ops, NULL);
}

