#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../global.h"
#include "../lib/io.h"
#include "../lib/str.h"
#include "../lib/path.h"

typedef unsigned long long ull;

void error_dir(char *dir) {
    error("cd %s: No such file or directory", dir);
}

int cd(char **argv) {
    char *dir = argv[0];

    // 引数なし
    if (dir == NULL) {
        cwd = getenv("HOME");
        return 0;
    }

    char start = dir[0];
    ull dir_len = strlen(dir);
    char *tmp;

    if (start == '/') {
        // 絶対パス (/**)
        tmp = dir;
    } else if (start == '~') {
        // ホームディレクトリ (~)
        if (dir_len > 1 && dir[1] != '/') {
            error_dir(dir);
            return 1;
        }

//        char *home = strdup(getenv("HOME")); // TODO: getenv("HOME");
        char *home = "/c/Users/harin";

        if (dir_len == 1) {
            tmp = home;
        } else {
            tmp = path_resolve(home, dir + 2);
        }
    } else {
        tmp = path_resolve(cwd, dir);
    }

//    debug("%s", tmp);

//    if (tmp == NULL) {
//        error_dir(dir);
//        return 1;
//    }
//
//    DIR *dfd = opendir(tmp);
//    if (dfd == NULL) {
//        error_dir(dir);
//        return 1;
//    }
//    closedir(dfd);

    // cwd を更新
    char *old = cwd;
    cwd = tmp;
    free(old);

//    debug("%s", cwd);
    return 0;
}
