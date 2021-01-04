/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:09 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:04:17 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_input(t_all *all, char quote_flag, char single_quote_flag)
{
	static char	*str_input;
	char		c;

	str_input = NULL;
	if (read(0, &c, 1) == 0 && str_input == NULL)
		ft_exit(all, NULL);
	while (c == ' ' || c == '\t')
		read(0, &c, 1);
	while (c != '\n' || quote_flag != 0 || single_quote_flag != 0)
	{
		if ((str_input = str_plus_char(str_input, c)) == NULL)
			return (NULL);
		if (c == '\\' && read(0, &c, 1))
		{
			if ((str_input = str_plus_char(str_input, c)) == NULL)
				return (NULL);
		}
		else if (c == '"' && single_quote_flag == 0)
			quote_flag = !quote_flag;
		else if (c == '\'' && quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		read(0, &c, 1);
	}
	return (str_input);
}

char	find_end_command(char sumbol, int *i, t_all *all)
{
	if (sumbol == ';')
	{
		*i += 1;
		return (1);
	}
	else if (sumbol == '|')
	{
		if (all->pipe == -1)
		{
			pipe(all->pipefd);
			all->pipe = 1;
		}
		else if (all->pipe == 0)
		{
			pipe(all->pipefd_second);
			all->pipe = 2;
		}
		*i += 1;
		return (1);
	}
	return (0);
}

char	*get_command(char *str_input, int *i, t_all *all)
{
	char	*command;
	char	quote_flag;
	char	single_quote_flag;

	command = NULL;
	quote_flag = 0;
	single_quote_flag = 0;
	while (str_input[*i] != '\0')
	{
		if (quote_flag == 0 && single_quote_flag == 0)
			if (find_end_command(str_input[*i], i, all) == 1)
				break ;
		if (str_input[*i] == '\'' && quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		else if (str_input[*i] == '\"' && single_quote_flag == 0)
			quote_flag = !quote_flag;
		else if (str_input[*i] == '\\')
		{
			command = str_plus_char(command, str_input[*i]);
			*i += 1;
		}
		command = str_plus_char(command, str_input[*i]);
		*i += 1;
	}
	return (command);
}

int		main(int argc, char **argv, char **envp)
{
	t_all	all;
	int		i;
	char	*str_input;
	char	*str;

	argv[argc] = NULL;
	if (envp != NULL && envp[0] != NULL)
		make_copy_envp(&all, envp);
	while (1)
	{
		i = 0;
		print_color_start(&all, 0);
		if ((str_input = read_input(&all, 0, 0)) && find_error(str_input) == 0)
		{
			while (str_input[i] != '\0')
			{
				str = get_command(str_input, &i, &all);
				division_command(&all, str);
				if (i == -1)
					break ;
			}
		}
		free(str_input);
	}
	return (0);
}
