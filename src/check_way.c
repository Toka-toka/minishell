/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:49 by white             #+#    #+#             */
/*   Updated: 2021/01/04 03:10:09 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**check_way3(t_all *all)
{
	char	**all_path;
	char	*path;

	if ((path = search_var(all, "PATH")) == NULL)
	{
		all_path = malloc(sizeof(char*) * 2);
		all_path[0] = getcwd(NULL, 0);
		all_path[1] = NULL;
	}
	else
	{
		all_path = ft_split(path, ':');
		if (all_path == NULL)
			critical_error("Check_way3", "Malloc problem", strerror(errno));
	}
	return (all_path);
}

char		*check_way2(t_all *all, char *command)
{
	int		fd;
	char	**all_path;
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	all_path = check_way3(all);
	while (all_path[i] != NULL)
	{
		temp = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(temp, command);
		free(temp);
		if ((fd = open(path, O_RDONLY)) != -1)
		{
			close(fd);
			break ;
		}
		free(path);
		path = NULL;
		i++;
	}
	free_arr((void **)all_path);
	return (path);
}

void		check_way(t_all *all, char *command, char **path)
{
	DIR		*dirp;

	*path = check_way2(all, command);
	dirp = NULL;
	if (*path == NULL || (dirp = opendir(*path)) != NULL)
	{
		if (dirp != NULL)
			closedir(dirp);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		all->status = 127;
		free(*path);
		*path = NULL;
	}
}
