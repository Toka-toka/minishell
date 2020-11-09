#include "../includes/minishell.h"

int main (int argc, char **argv, char **envp)
{
    int i  = 0;
    char *path;

    path = NULL;
    path = getcwd(NULL, 0);
    free(path);
    printf("path = %s\n", path);
    while (envp[i] != NULL)
    {
        printf("envp[%d] = %s\n", i, envp[i]);
        i++;
    }
    return(0);
}