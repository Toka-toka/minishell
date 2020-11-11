#include "../includes/minishell.h"

void	**make_copy_envp(t_all *all, char **envp)
{
	int i;
	int len;
	char **copy;
	static t_envp *env;
	t_envp *temp;
//	char abc;

	i = 0;
/*	while (envp[i] != NULL)
		i++;
	copy = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i] != NULL)
		copy[i++] = ft_strdup(envp[i]);
	copy[i] = NULL; */
//	scanf("%c", abc);
	env = (t_envp *)malloc(sizeof(t_envp));
    env->value = ft_strdup(envp[i]);
    env->next = NULL;
	all->envp = env;
	i++;
//	env = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
	temp = all->envp;
//	scanf("%c", abc);
	while (temp->next != NULL)
	{
		printf("list cont = %s\n", temp->value);
		temp = temp->next;
	}
}

int main (int argc, char **argv, char **envp)
{
    t_all	all;
	int		i = 0;
    char	*path;
	int abc;

//	scanf("%d", &abc);
	make_copy_envp(&all, envp);
  //  path = NULL;
 //   path = getcwd(NULL, 0);
  //  printf("path = %s\n", path);
  //  free(path);
/*    while (envp[i] != NULL)
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
	}*/
    return(0);
}