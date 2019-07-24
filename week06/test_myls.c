#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
# include <bsd/string.h>
#endif
#include <sysexits.h>
#include <unistd.h>

#define MAXDIRNAME 256
#define MAXFNAME 256
#define MAXNAME 24

int main (int argc, char* argv[])
{
    char dirname[256] = ".";
    strlcpy (dirname, argv[1], 256);
    struct stat info;
     if (stat (dirname, &info) <0)
         err (EX_OSERR, "%s", dirname);
    
    if (!S_ISDIR (info.st_mode)) {
        errno = ENOTDIR;
        err (EX_DATAERR, "%s", dirname);
    }

    return 0;
}