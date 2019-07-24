// myls.c ... my very own "ls" implementation

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

char *rwxmode (mode_t, char *);
char *username (uid_t, char *);
char *groupname (gid_t, char *);

int main (int argc, char *argv[])
{
	// string buffers for various names
	 char uname[MAXNAME+1];
	 char gname[MAXNAME+1];
	 char mode[MAXNAME+1] = {'\0'};

	// collect the directory name, with "." as default
	char dirname[MAXDIRNAME] = ".";
	if (argc >= 2)
		strlcpy (dirname, argv[1], MAXDIRNAME);

	// check that the name really is a directory
	struct stat info;
	if (stat (dirname, &info) < 0)
		err (EX_OSERR, "%s", dirname);

	if (! S_ISDIR (info.st_mode)) {
		errno = ENOTDIR;
		err (EX_DATAERR, "%s", dirname);
	}

	DIR *df = opendir(dirname);
	struct dirent *entry;
	while ((entry = readdir(df)) !=  NULL) {
		//ignore the object if its name starts with '.'
		if (entry->d_name[0] ==  '.') {
			continue;
		}
		//update rwxmode
		rwxmode(info.st_mode, mode); 
		//update info
		lstat(entry->d_name, &info);
		//print it
		printf("%s  %-8.8s %-8.8s %8lld  %s\n",rwxmode(info.st_mode, mode), username(info.st_uid, uname), groupname(info.st_gid, gname), info.st_size, entry->d_name);
	}
	// finish up
	closedir(df); 

	return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode (mode_t mode, char *str)
{
	//set str to '---------'
	for (int i = 0; i < 9; i++) {
		str[i] = '-';
	}
	//check the mode
	switch (mode & S_IFMT) {
	case S_IFDIR:	//if it is directory
		str[0] = 'd';
		break;
	case S_IFREG:	//if it is regular file
		str[0] = '-';
		break;
	case S_IFLNK:	//if it is symbolic link
		str[0] = 'l';
		break;
	default:
		str[0] = '?';
		break;
	}

	//check permission for owner
	int check = mode & S_IRWXU;
	str[1] = ((check & S_IRUSR)) == S_IRUSR ?  'r' : '-';
	str[2] = ((check & S_IWUSR)) == S_IWUSR ?  'w' : '-';
	str[3] = ((check & S_IXUSR)) == S_IXUSR ?  'x' : '-';

	//check permission for group
	check = mode & S_IRWXG;
	str[4] = ((check & S_IRGRP)) == S_IRGRP ?  'r' : '-';
	str[5] = ((check & S_IWGRP)) == S_IWGRP ?  'w' : '-';
	str[6] = ((check & S_IXGRP)) == S_IXGRP ?  'x' : '-';

	//check permission for others
	check = mode & S_IRWXO;
	str[7] = ((check & S_IROTH)) == S_IROTH ?  'r' : '-';
	str[8] = ((check & S_IWOTH)) == S_IWOTH ?  'w' : '-';
	str[9] = ((check & S_IXOTH) == S_IXOTH) ?  'x' : '-';
	return str;
}

// convert user id to user name
char *username (uid_t uid, char *name)
{
	struct passwd *uinfo = getpwuid (uid);
	if (uinfo != NULL)
		snprintf (name, MAXNAME, "%s", uinfo->pw_name);
	else
		snprintf (name, MAXNAME, "%d?", (int) uid);
	return name;
}

// convert group id to group name
char *groupname (gid_t gid, char *name)
{
	struct group *ginfo = getgrgid (gid);
	if (ginfo != NULL)
		snprintf (name, MAXNAME, "%s", ginfo->gr_name);
	else
		snprintf (name, MAXNAME, "%d?", (int) gid);
	return name;
}
