/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:53:38 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:07:09 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	print_error(char *error_str, char *sumbol)
{
	int		i;

	write(1, "minishell: ", 7);
	i = 0;
	while (error_str != NULL && error_str[i] != '\0')
		i++;
	write(1, error_str, i);
	i = 0;
	while (sumbol[i] != '\0')
		i++;
	write(1, sumbol, i);
	write(1, "\n", 1);
	return (-1);
}

char	find_error_redirect(char *str_input, int i, char sumblol)
{
	int		count;

	count = 0;
	while (str_input[i] == sumblol)
	{
		count++;
		i++;
	}
	if (count >= 3)
	{
		if (sumblol == '>')
			return (print_error("syntax error near unexpected token `", ">>"));
		else
			return (print_error("syntax error near unexpected token `", "<<"));
	}
	if (str_input[i] == '\0')
		return (print_error("syntax error near unexpected token `", "newline"));
	else if (str_input[i] == ';')
		return (print_error("syntax error near unexpected token `", ";"));
	else if (str_input[i] == '|')
		return (print_error("syntax error near unexpected token `", "|"));
	return (0);
}

char	error_sumbol(char *str_input, int i)
{
	int		j;

	if (str_input[i] == ';' || str_input[i] == '|')
	{
		j = i;
		while (str_input[++j] != '\0')
		{
			if (str_input[j] != ' ')
				break ;
		}
		if (str_input[j] == ';' || str_input[j] == '|' || i == 0)
		{
			str_input[i + 1] = '\0';
			return (print_error("syntax error near unexpected token `",
				str_input + i));
		}
	}
	return (0);
}

char	find_error(char *str_input)
{
	char	quote[2];
	int		i;

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str_input[i] != '\0')
	{
		if (quote[0] == 0 && quote[1] == 0 && error_sumbol(str_input, i) != 0)
			return (-1);
		if (str_input[i] == '>' || str_input[i] == '<')
		{
			if (find_error_redirect(str_input, i, str_input[i]) == -1)
				return (-1);
		}
		else if (str_input[i] == '\'')
			quote[1] = !quote[1];
		else if (str_input[i] == '\"')
			quote[0] = !quote[0];
		else if (str_input[i] == '\\')
			i++;
		i++;
	}
	return (0);
}
