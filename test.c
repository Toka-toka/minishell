#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    DIR *dirp;
    struct dirent *dp;
	int fd1;
	int fd2;
	int fd3;
    int fd4;
    int fd5;
    int fd6;
    
    dirp = opendir("/bin");
    if (dirp == NULL)
        return (1);
//    len = strlen(name);
    while ((dp = readdir(dirp)) != NULL)
    {
        if (dp->d_type == DT_REG)
            printf("name = %s\n", dp->d_name);
    }
    (void)closedir(dirp);
	fd1 = open("./ls/ls1", O_RDONLY | S_IXUSR);
    printf("fd1 = %d errno = %d, error = %s\n", fd1, errno, strerror(errno));
    errno = 0;
	fd2 = open ("./ls/ls2", O_RDONLY | S_IXUSR);
    printf("fd2 = %d errno = %d, error = %s\n", fd2, errno, strerror(errno));
    errno = 0;
	fd3 = open("./ls/ls3", O_RDONLY | S_IXUSR);
    printf("fd3 = %d errno = %d, error = %s\n", fd3, errno, strerror(errno));
    errno = 0;
    fd4 = open("./ls/ls4", O_RDONLY | S_IXUSR);
    printf("fd4 = %d errno = %d, error = %s\n", fd4, errno, strerror(errno));
    errno = 0;
    fd5 = open("/Users/sedric/Desktop/minishell/ls/ls5", O_WRONLY | S_IXUSR);
    printf("fd5 = %d errno = %d, error = %s\n", fd5, errno, strerror(errno));
    fd6 = open("/bin/ls", O_RDONLY | S_IXUSR);
    printf("fd6 = %d errno = %d, error = %s\n", fd6, errno, strerror(errno));
    fd6 = open("/bin/echo", O_RDONLY | S_IXUSR);
    printf("fd6 = %d errno = %d, error = %s\n", fd6, errno, strerror(errno));
    
    return (0);
}
