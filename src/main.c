#include "../includes/minishell.h"

int main (int argc, char **argv, char **envp)
{
    int		i = 0;
    char	*path;

    path = NULL;
    path = getcwd(NULL, 0);
    printf("path = %s\n", path);
    free(path);
    while (envp[i] != NULL)
    {
        printf("envp[%d] = %s\n", i, envp[i]);
        i++;
    }
    printf("\n\n");
	char	command[BUFSIZ];
	int		status;
	pid_t	pid;

	while (1)
	{
		printf("simpsh:  ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			return (0);
		}

		char	**str = (char **)malloc(4 * 8);
		str[0] = "ls";
		str[1] = "-l";
		str[2] = "AAA 123";
		str[2] = NULL;
	
		command[strlen(command) - 1] = '\0';
		if ((pid = fork()) == 0)
			execve("/bin", str, envp);
		
		while(wait(&status) != pid)
			continue;
		
		printf("\n");
	}


    return(0);
}