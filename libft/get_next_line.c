/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 23:51:35 by sedric            #+#    #+#             */
/*   Updated: 2020/07/29 23:55:43 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		strchr_int(const char *s, int c)
{
	char		*str;
	char		symbol;
	int			i;

	i = 0;
	symbol = (char)c;
	str = (char*)s;
	while (str[i] != '\0')
	{
		if (str[i] == symbol)
			return (i);
		i++;
	}
	return (c == '\0' ? i : -1);
}

static int		join_call(char **line, char *buff, int *start)
{
	int		sym_index;
	char	*temp;

	temp = *line;
	if ((sym_index = strchr_int(buff, '\n')) == -1)
	{
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
		free(temp);
		*start = 0;
		return (2);
	}
	buff[sym_index] = '\0';
	if (!(*line = ft_strjoin(*line, buff)))
		return (-1);
	free(temp);
	*start += sym_index + 1;
	return (1);
}

static int		read_call(int fd, char **buff)
{
	int			status;

	if (!(*buff = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	status = read(fd, *buff, BUFFER_SIZE);
	buff[0][status] = '\0';
	return (status);
}

int				get_next_line(int fd, char **line)
{
	static char	*buff;
	static int	start;
	int			status;

	status = 2;
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	*line = malloc(sizeof(char) * 1);
	*line[0] = '\0';
	while (status == 2)
	{
		if (start == 0)
			status = read_call(fd, &buff);
		if (status > 0)
			status = join_call(line, buff + start, &start);
		if (status != 1 || start == BUFFER_SIZE)
		{
			start = 0;
			free(buff);
		}
	}
	return (status);
}
