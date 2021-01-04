/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_standart_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:47:11 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:10:08 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	init_str(char *init_str, char *src, int *i)
{
	int		j;

	j = 0;
	if (src != NULL)
	{
		while (src[j] != '\0')
		{
			init_str[*i] = src[j];
			*i += 1;
			j += 1;
		}
	}
}

char	*str_plus_str(char *src, char *dest)
{
	int		i;
	int		len;
	char	*str;

	if (src == NULL && dest == NULL)
		return (NULL);
	len = 0;
	if (src != NULL)
		len += ft_strlen(src);
	if (dest != NULL)
		len += ft_strlen(dest);
	if ((str = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	init_str(str, src, &i);
	free(src);
	init_str(str, dest, &i);
	str[i++] = '\0';
	return (str);
}

char	*str_plus_char(char *src, char c)
{
	char	*dest;
	int		i;

	i = 0;
	if (src != NULL)
	{
		if ((dest = (char *)malloc(ft_strlen(src) + 2)) == NULL)
		{
			free(src);
			return (NULL);
		}
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	else if ((dest = (char *)malloc(2)) == NULL)
		return (NULL);
	dest[i] = c;
	dest[i + 1] = '\0';
	free(src);
	return (dest);
}

char	*number_to_str(char *command, int status)
{
	int		i;
	int		number;

	i = 1;
	number = status;
	while (number > 9)
	{
		i++;
		number = number / 10;
	}
	number = 1;
	while (i > 1)
	{
		number *= 10;
		i -= 1;
	}
	while (number != 0)
	{
		command = str_plus_char(command, status / number + 48);
		status = status % number;
		number = number / 10;
	}
	return (command);
}
