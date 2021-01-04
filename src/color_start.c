/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:56 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:02:32 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn(int sig)
{
	print_color_start(NULL, sig);
}

void	make_copy_envp(t_all *all, char **envp)
{
	int i;

	i = 0;
	all->envp = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
	all->standart_fd[0] = dup(0);
	all->standart_fd[1] = dup(1);
	all->input = -1;
	all->output = -1;
	all->pipe = -1;
	all->fork = 0;
	all->status = 0;
	signal(SIGINT, &fn);
	signal(SIGQUIT, &fn);
}

void	print_used_or_dir(t_all *all, char *src)
{
	char	*name;

	name = search_var(all, src);
	if (name != NULL)
		write(0, name, ft_strlen(name));
	else
		write(0, "None", ft_strlen("None"));
}

void	print_color_start(t_all *all, int sig)
{
	static	t_all *temp;

	if (temp == NULL)
		temp = all;
	temp->pipe = -1;
	if (sig == SIGQUIT && temp->fork == 0)
		write(1, "\b\b  \b\b", 6);
	if (sig != 0 && temp->fork == 0 && sig != SIGQUIT)
		write(0, "\n", 1);
	if (temp->fork == 0 && (sig == SIGINT || sig == 0))
	{
		write(0, "\033[1;31m┌─[\033[1;34m", 21);
		print_used_or_dir(temp, "USERNAME");
		write(0, "\033[1;31m]-[\033[1;34m", 17);
		print_used_or_dir(temp, "PWD");
		write(0, "\033[1;31m", 7);
		write(0, "]\n", 2);
		write(0, "└──╼ ", 14);
		write(0, "\033[1;33m", 7);
		write(0, "$", 1);
		write(0, "\033[0m", 4);
		if (sig == SIGINT)
			temp->status = 130;
	}
}
