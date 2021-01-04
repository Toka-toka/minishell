/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_echo_and_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:06:20 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:07:13 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	output_to_file(t_all *all, int *i, char *str, char *file_name)
{
	if (str[*i] == '>')
	{
		*i = read_word(all, str, &file_name, *i + 1);
		all->output = open(file_name, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
	}
	else
	{
		*i = read_word(all, str, &file_name, *i);
		all->output = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	}
	if (all->output == -1)
	{
		print_err("minishell", file_name, strerror(errno));
		free(file_name);
		return (-1);
	}
	free(file_name);
	return (1);
}

char	redirect_file(t_all *all, int *i, char *str)
{
	char	*file_name;
	int		j;

	file_name = NULL;
	*i += 1;
	j = 0;
	if (str[*i - 1] == '>')
	{
		if (output_to_file(all, i, str, file_name) == -1)
			j = -1;
	}
	else if (str[*i - 1] == '<')
	{
		*i = read_word(all, str, &file_name, *i);
		all->input = open(file_name, O_RDWR);
		if (all->input == -1)
		{
			print_err("minishell", file_name, strerror(errno));
			j = -1;
		}
	}
	free(file_name);
	return (j);
}

int		for_echo(t_all *all, char *array, char **command, int *i)
{
	char	*name;

	name = NULL;
	while (ft_isalnum(array[*i]) || array[*i] == '_')
	{
		name = str_plus_char(name, array[*i]);
		*i += 1;
		if (name[0] >= '0' && name[0] <= '9')
		{
			free(name);
			return (0);
		}
	}
	if (name == NULL)
		*command = str_plus_char(*command, '\0');
	else
		*command = str_plus_str(*command, search_var(all, name));
	free(name);
	return (0);
}

int		read_for_echo(t_all *all, char *array, char **command, int *i)
{
	*i += 1;
	if (array[*i] == '?')
	{
		*command = number_to_str(*command, all->status);
		*i += 2;
	}
	else
	{
		if (for_echo(all, array, command, i) == 0)
			return (0);
	}
	*i -= 1;
	return (1);
}
