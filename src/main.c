#include "../includes/minishell.h"

void	free_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	fn(int sig)
{
	print_color_start(NULL, sig);
}

void	**make_copy_envp(t_all *all, char **envp)
{
	int i;
//	t_envp *temp;

	i = 0;
	all->envp = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i], 0);
		i++;
	}
	all->standart_fd[0] = dup(0);
	all->standart_fd[1] = dup(1);
	all->standart_fd[2] = dup(2);
	
	all->pipe = -1;
	all->fork = 0;
	all->status = 0;
//	signal(SIGINT, &fn);
//	signal(SIGQUIT, &fn);
//	signal(SIGTSTP, &fn);
}

char	print_error(char *sumbol)
{
	int		i;

	i = 0;
	write(1, "bash: syntax error near unexpected token `", 43);
	while (sumbol[i] != '\0')
		i++;
	write(1, sumbol, i);
	write(1, "\'\n", 2);
	return (1);
}

char	find_error(char *str_input)
{
	char	quote_flag;
	char	single_quote_flag;
	int		i;
	int		j;

	i = 0;
	quote_flag = 0;
	single_quote_flag = 0;
	while (str_input[i] != '\0')
	{
		if (str_input[i] == ';' && quote_flag == 0 && single_quote_flag == 0)
		{
			j = i;
			while (str_input[++j] != '\0')
			{
				if (str_input[j] != ' ')
					break;
			}
			if (str_input[j] == ';' || str_input[j] == '|' || i == 0)
			{
				str_input[i + 1] = '\0';
				return (print_error(str_input + i));
			}
		}
		else if (str_input[i] == '|' && quote_flag == 0 && single_quote_flag == 0)
		{
			j = i;
			while (str_input[++j] != '\0')
			{
				if (str_input[j] != ' ')
					break;
			}
			if (str_input[j] == ';' || str_input[j] == '|' || i == 0)
			{
				str_input[i + 1] = '\0';
				return (print_error(str_input + i));
			}
		}
		else if (str_input[i] == '\'')
		{
			single_quote_flag = !single_quote_flag;
		}
		else if (str_input[i] == '\"')
		{
			quote_flag = !quote_flag;
		}
		i++;
	}
	return (0);
}

char	*read_input(void)
{
	char	*str_input;
	char	c;
	char	quote_flag;
	char	single_quote_flag;

	quote_flag = 0;
	single_quote_flag = 0;
	str_input = NULL;
	if (read(0, &c, 1) == 0 && str_input == NULL)
		exit(1);
	while (c == ' ' || c == '\t')
		read(0, &c, 1);
	while (c != '\n' || quote_flag != 0 || single_quote_flag != 0)
	{
		str_input = str_plus_char(str_input, c);
		if (c == '\\' && read(0, &c, 1))
			str_input = str_plus_char(str_input, c);
		else if (c == '"' && single_quote_flag == 0)
			quote_flag = !quote_flag;
		else if (c == '\'' && quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		while (read(0, &c, 1) == 0)
			;
	}
	return (str_input);
}

char	*get_command(char *str_input, int *i, t_all *all)
{
	char	*command;
	char	quote_flag;
	char	single_quote_flag;

	all->input = -1;
	all->output = -1;
//	close(all->input);
//	close(all->output);

	command = NULL;
	quote_flag = 0;
	single_quote_flag = 0;
	while (str_input[*i] != '\0')
	{
		if (str_input[*i] == ';' && quote_flag == 0 && single_quote_flag == 0)
			break;
		else if (str_input[*i] == '\'')
			single_quote_flag = !single_quote_flag;
		else if (str_input[*i] == '\"')
			quote_flag = !quote_flag;
		else if (str_input[*i] == '\\')
		{
			command = str_plus_char(command, str_input[*i]);
			*i += 1;
		}
		else if (str_input[*i] == '|' && quote_flag == 0 && single_quote_flag == 0)
		{
			if (all->pipe == -1)
			{
				pipe(all->pipefd);
				all->pipe = 1;
			}
			if (all->pipe == 0)
			{
				pipe(all->pipefd_second);
				all->pipe = 2;	
			}
			break;
		}
		command = str_plus_char(command, str_input[*i]);
		*i += 1;
	}
	if (str_input[*i] != '\0')
		*i += 1;
	return (command);
}

int		main (int argc, char **argv, char **envp)
{
    t_all	all;
	int		i;
	char	*str_input;
	char	*str;

	if (envp != NULL && envp[0] != NULL)	// Подумать над этим. 			Над чем подумать?
		make_copy_envp(&all, envp);
	while (1)
	{
		i = 0;
		print_color_start(&all, 0);
		str_input = read_input();
		if (str_input == NULL || find_error(str_input))
		{
			free(str_input);
			continue;
		}
		while (str_input[i] != '\0')
		{
			str = get_command(str_input, &i, &all);
			//if (str_input[i] != '\0')
			//	i++;
			division_command(&all, str);
			free(str);
		}
		free(str_input);
	}
    return(0);
}