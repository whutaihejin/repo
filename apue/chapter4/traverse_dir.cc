#include <unistd.h>
#include <string>
#include <getopt.h>
#include <sys/stat.h>
#include <dirent.h>

#include "apue.h"

void Usage() {
    printf("usage: \n  -d <directory>\n  -h show help message\n");
}

struct Statistic {
    Statistic():
        reg(0), blk(0), cha(0),
        fifo(0), slink(0), sock(0), dir(0) {}
    size_t reg;
    size_t blk;
    size_t cha;
    size_t fifo;
    size_t slink;
    size_t sock;
    size_t dir;

    void Display() {
        size_t total = reg + blk + cha
            + fifo + slink + sock + dir;
        printf("total entry:%ld\n", (long)total);
        total = total <= 0 ? 1 : total;
        printf("reg: %ld/%ld = %.2f\n", (long)reg, (long)total, reg * 100.0 / total);
        printf("blk: %ld/%ld = %.2f\n", (long)blk, (long)total, blk * 100.0 / total);
        printf("cha: %ld/%ld = %.2f\n", (long)cha, (long)total, cha * 100.0 / total);
        printf("fifo: %ld/%ld = %.2f\n", (long)fifo, (long)total, fifo* 100.0 / total);
        printf("slink: %ld/%ld = %.2f\n", (long)slink, (long)total, slink * 100.0 / total);
        printf("sock: %ld/%ld = %.2f\n", (long)sock, (long)total, sock * 100.0 / total);
        printf("dir: %ld/%ld = %.2f\n", (long)dir, (long)total, dir * 100.0 / total);
    }
};

// traverse type
enum Type {
    F_FILE,
    F_DIR,
    F_DIR_NR,
    F_NSTAT
};

// traverse dir
int Traverse(std::string*);
int Statistic(std::string*, struct stat*, Type);

struct Statistic statistic;

int main(int argc, char* argv[]) {
    const char* dir = nullptr;
    int opt;
    while ((opt = getopt(argc, argv, "hd:")) != -1) {
        switch (opt) {
            case 'd':
                dir = optarg;
                break;
            case 'h':
                // througout here
            default:
                Usage();
                return 0;
        }
    }
    if (dir == nullptr) {
        Usage();
        return 0;
    }
    std::string path(dir);
    printf("=== %s ===\n", path.c_str());
    Traverse(&path);
    statistic.Display();
    return 0;
}

int Traverse(std::string* path) {
    struct stat buf;
    // stat
    if (lstat(path->c_str(), &buf) < 0) {
        return Statistic(path, &buf, F_NSTAT);
    }
    // whether a directory
    if (!S_ISDIR(buf.st_mode)) {
        return Statistic(path, &buf, F_FILE);
    } else {
        Statistic(path, &buf, F_DIR);
    }
    // traverse dir
    DIR* dp;
    struct dirent* ent;
    if ((dp = opendir(path->c_str())) == NULL) {
        return Statistic(path, &buf, F_DIR_NR);
    }
    int origin_limit = path->size();
    // path->append('/', 1);
    path->append("/");
    while ((ent = readdir(dp)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        int limit = path->size();
        path->append(ent->d_name);
        Traverse(path);
        path->resize(limit);
    }
    path->resize(origin_limit);
    return closedir(dp);
}

int Statistic(std::string* path, struct stat* buf, Type type) {
    switch (type) {
        case F_FILE:
            switch (buf->st_mode & S_IFMT) {
                case S_IFREG:
                    statistic.reg++; break;
                case S_IFBLK:
                    statistic.blk++; break;
                case S_IFCHR:
                    statistic.cha++; break;
                case S_IFIFO:
                    statistic.fifo++; break;
                case S_IFLNK:
                    statistic.slink++; break;
                case S_IFSOCK:
                    statistic.sock++; break;
                case S_IFDIR:
                    statistic.dir++; break;
                default:
                    printf("unknown file type\n");
            }
        case F_DIR:
            statistic.dir++; break;
        case F_DIR_NR:
            printf("can't read directory: %s\n", path->c_str());
            break;
        case F_NSTAT:
            printf("can't stat: %s\n", path->c_str());
            break;
        default:
            printf("unknown path type %s\n", path->c_str());
    }
    return 0;
}
