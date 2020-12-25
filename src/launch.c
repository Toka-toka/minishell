#include "../includes/minishell.h"

void	pipe_before_command(t_all *all, int *output_fd, int *input_fd)
{
	if (all->pipe == 1)
	{
		if (all->input != -1)
			*input_fd = all->input;
		*output_fd = (all->output != -1) ? all->output: all->pipefd[1];
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
	dup2(all->standart_fd[0], 0);
	dup2(all->standart_fd[1], 1);
	dup2(all->standart_fd[2], 2);
}

void	division_command(t_all *all, char *array)
{
	char	*command;
    char    *way;
	char	**arg;
	int		i;
	int		output_fd;
	int		input_fd;

	i = 0;
	command = NULL;
	if (array == NULL)
		return ;
	read_word(all, array, &command, i);
	arg = read_arg(all, array, &i);			// поправить передаваемые значения

	output_fd = all->standart_fd[1];
	input_fd = all->standart_fd[0];

	pipe_before_command(all, &output_fd, &input_fd);
	dup2(output_fd, 1);
	dup2(input_fd, 0);
	run_manager(all, arg, command);
	pipe_after_command(all);
}