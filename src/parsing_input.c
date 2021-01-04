/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:17 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:06:56 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_word_two(char quotes_flag[2], char **command, int *i, char *array)
{
	if (array[*i] == '\"' && quotes_flag[1] == 0)
		quotes_flag[0] = !quotes_flag[0];
	else if (array[*i] == '\\' && quotes_flag[1] == 0)
	{
		*i += 2;
		*command = str_plus_char(*command, array[*i - 1]);
	}
	else if ((array[*i] == '\'' || quotes_flag[1] == 1) && quotes_flag[0] == 0)
	{
		if (array[*i] == '\'')
			quotes_flag[1] = !quotes_flag[1];
		else
			*command = str_plus_char(*command, array[*i]);
	}
	else
		*command = str_plus_char(*command, array[*i]);
	if (array[*i] != '\0')
		*i += 1;
}

int		read_word(t_all *all, char *array, char **command, int i)
{
	char	quotes_flag[2];

	quotes_flag[0] = 0;
	quotes_flag[1] = 0;
	while (array[i] != '\0' && (array[i] == ' ' || array[i] == '\t'))
		i++;
	while (array[i] != '\0')
	{
		if (array[i] == '$' && quotes_flag[1] == 0)
			read_for_echo(all, array, command, &i);
		else if (array[i] == ' ' && quotes_flag[0] == 0)
			break ;
		else if ((array[i] == '>' || array[i] == '<')
				&& quotes_flag[1] == 0 && quotes_flag[0] == 0)
		{
			if (redirect_file(all, &i, array) != 0)
				return (-1);
		}
		else
			read_word_two(quotes_flag, command, &i, array);
	}
	return (i);
}

int		number_word(char *array, int i)
{
	char	word_flag;
	char	arg_flag;
	int		number;

	word_flag = 1;
	arg_flag = 0;
	number = 0;
	while (array[i] != '\0' && array[i] != ';' && array[i] != '|')
	{
		if (array[i] == '\"')
			arg_flag = !arg_flag;
		if (array[i] != ' ' && arg_flag != 1)
		{
			if (word_flag != 0)
				number += 1;
		}
		else
			word_flag = 1;
		i++;
	}
	return (number);
}

char	**read_arg(t_all *all, char *array, int *i)
{
	char	**arg;
	int		len;
	int		j;

	len = 1 + number_word(array, *i);
	arg = (char **)malloc((len + 1) * sizeof(char *));
	if (arg == NULL)
		return (NULL);
	j = 0;
	while (j < len && array[*i] != '\0')
	{
		arg[j] = NULL;
		*i = read_word(all, array, &arg[j], *i);
		if (*i == -1)
		{
			free_arg(arg);
			return (NULL);
		}
		if (arg[j] != NULL)
			j++;
	}
	arg[j] = NULL;
	return (arg);
}
