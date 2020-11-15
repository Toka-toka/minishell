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
//	t_envp *temp;

	i = 0;
	all->envp = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
}

char	*read_array(void)
{
	char	*array;
	char	c;

	array = NULL;
	while (read(0, &c, 1))
	{
		if (c == '\n')
			break;
		array = str_plus_char(array, c);
		if (c == '|' || c == ';')
			break;
	}
	return(array);
}

int main (int argc, char **argv, char **envp)
{
    t_all	all;
	char	*array;

	if (envp != NULL && envp[0] != NULL)	// Подумать над этим
		make_copy_envp(&all, envp);	
	while (1)
	{
		print_color_start(&all);
		array = read_array();				// Поместил эту функцию в main
		division_command(&all, array);
		free(array);
	}
    return(0);
}