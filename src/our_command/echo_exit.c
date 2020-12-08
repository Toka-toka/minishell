/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 22:02:38 by sedric            #+#    #+#             */
/*   Updated: 2020/12/08 22:02:40 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		del_all_var(t_all *all)
{
	t_envp	*current;

	current = all->envp;
	while (all->envp != NULL)
	{
		current = all->envp;
		all->envp = all->envp->next;
		free(current->name);
		free(current->value);
		free(current);
	}
}

void		print_err(char *function, char *arg, char *err)
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
}

void		ft_echo(t_all *all, char **arg)
{
	int		i;
	char	n_flag;

	i = 1;
	n_flag = 0;
	while (ft_strcmp(arg[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		i++;
		if (arg[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", 1);
	all->status = 0;
}

int			ckeck_exit_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void		ft_exit(t_all *all, char **arg)
{
	unsigned char	status;
	int				i;

	i = 0;
	if (arg[1] == NULL)
		status = 0;
	else if (arg[1] != NULL && (ckeck_exit_arg(arg[1]) == 1))
	{
		print_err("exit", arg[1], "numeric argument required");
		status = 2;
	}
	else if (arg[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		status = 1;
	}
	else
		status = ft_atoi(arg[1]);
	if (all->pipe == -1 && status != 1)
	{
		del_all_var(all);
		exit(status);
	}
	else
		all->status = status;
}
