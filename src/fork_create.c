/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:37 by white             #+#    #+#             */
/*   Updated: 2021/01/03 06:33:38 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**arr_from_list(t_all *all)
{
	t_envp	*current;
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	current = all->envp;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	current = all->envp;
	i = 0;
	while (current != NULL)
	{
		temp = ft_strjoin(current->name, "=");
		arr[i] = ft_strjoin(temp, current->value);
		free(temp);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

void		child_work(t_all *all, char *path, char **arg,
			void (*function)(t_all *all, char **arg))
{
	char	**envp;

	if (function != NULL)
	{
		function(all, arg);
		exit(all->status);
	}
	envp = arr_from_list(all);
	if (execve(path, arg, envp) == -1)
	{
		free_arr((void**)envp);
		if (errno == 13)
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		ft_putstr_fd("Execve return -1, exit code = errno\n", 2);
		exit(errno);
	}
	free_arr((void**)envp);
}

void		parent_work(t_all *all, pid_t pid)
{
	int		status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		all->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		all->status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		all->status = 128 + WSTOPSIG(status);
	all->fork = 0;
}

void		critical_error(char *function, char *arg, char *err)
{
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": ", 2);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void		fork_create(t_all *all, char *path, char **arg,
			void (*function)(t_all *all, char **arg))
{
	pid_t	pid;

	errno = 0;
	pid = fork();
	if (pid == -1)
		critical_error("Fork_create", "Fork didn't create", strerror(errno));
	all->fork = 1;
	if (pid == 0)
		child_work(all, path, arg, function);
	if (pid > 0)
		parent_work(all, pid);
}
