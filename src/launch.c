/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:12 by white             #+#    #+#             */
/*   Updated: 2021/01/04 19:52:43 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_before_command(t_all *all, int *output_fd, int *input_fd)
{
	if (all->pipe == 1)
	{
		if (all->input != -1)
			*input_fd = all->input;
		*output_fd = (all->output != -1) ? all->output : all->pipefd[1];
	}
	else if (all->pipe == 0)
	{
		*input_fd = (all->input != -1) ? all->input : all->pipefd[0];
		if (all->output != -1)
			*output_fd = all->output;
	}
	else if (all->pipe == 2)
	{
		*input_fd = (all->input != -1) ? all->input : all->pipefd[0];
		*output_fd = (all->output != -1) ? all->output : all->pipefd_second[1];
	}
	else if (all->pipe == -1)
	{
		if (all->input != -1)
			*input_fd = all->input;
		if (all->output != -1)
			*output_fd = all->output;
	}
}

void	pipe_after_command(t_all *all)
{
	if (all->pipe == 1)
	{
		all->pipe = 0;
		close(all->pipefd[1]);
	}
	else if (all->pipe == 0)
	{
		all->pipe = -1;
		close(all->pipefd[0]);
	}
	else if (all->pipe == 2)
	{
		close(all->pipefd[0]);
		dup2(all->pipefd_second[0], all->pipefd[0]);
		dup2(all->pipefd_second[1], all->pipefd[1]);
		close(all->pipefd[1]);
		close(all->pipefd_second[1]);
		all->pipe = 0;
	}
	all->input = -1;
	all->output = -1;
	dup2(all->standart_fd[0], 0);
	dup2(all->standart_fd[1], 1);
}

void	division_command(t_all *all, char *array)
{
	char	**arg;
	int		i;
	int		output_fd;
	int		input_fd;

	i = 0;
	if (array == NULL)
		return ;
	arg = read_arg(all, array, &i);
	if (arg != NULL)
	{
		output_fd = all->standart_fd[1];
		input_fd = all->standart_fd[0];
		pipe_before_command(all, &output_fd, &input_fd);
		dup2(output_fd, 1);
		dup2(input_fd, 0);
		if (arg != NULL && arg[0] != NULL)
			run_manager(all, arg);
		pipe_after_command(all);
	}
	free(array);
	free_arg(arg);
}
