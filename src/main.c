#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	**make_copy_envp(t_all *all, char **envp)
{
	int i;
	int len;
	char **copy;
	t_envp *temp;
	char	**arr;

	i = 0;
	all->envp->value = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
	temp = all->envp;
	i = 0;
/*	while (temp != NULL)
	{
		printf("%d |%s=%s\n%d |%s\n", i, temp->name, temp->value, i, envp[i]);
		putstr(temp->value);
		putstr("\n");
		temp = temp->next;
		i++;
	}*/
//	print_envp(all, 1);
	printf("all = %p\n", all);
	arr = arr_from_list(all);
	while (arr[i] != NULL)
	{
		ft_putstr(arr[i]);
		ft_putstr("\n");
		i++;
	}
}



int main (int argc, char **argv, char **envp)
{
    t_all	all;
	t_envp	env;
	/*
    int		i = 0;
    char	*path;

//	scanf("%d", &abc);
	all.envp = &env;
	if (envp != NULL && envp[0] != NULL) // подумать над этим
		make_copy_envp(&all, envp); // вернуть листы
  //  path = NULL;
 //   path = getcwd(NULL, 0);
  //  printf("path = %s\n", path);
  //  free(path);
/*    while (envp[i] != NULL)
    {
        printf("envp[%d] = %s\n", i, envp[i]);l
        i++;
    }
    */
	char	*array;
	char	c;

	while (1)
	{
		print_start_command();
		array = read_array();
		division_command(array);
		//printf("command = %s\n", array);
		free(array);
	}

	/*
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