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
	t_envp *temp;

	i = 0;
	all->envp->value = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
}

int main (int argc, char **argv, char **envp)
{
    t_all	all;
	t_envp	env;
	char	*array;

	all.envp = &env;
	if (envp != NULL && envp[0] != NULL) // подумать над этим
		make_copy_envp(&all, envp);	
	while (1)
	{
		print_start_command(&all);
		array = read_array();
		division_command(array);
		free(array);
	}
    return(0);
}