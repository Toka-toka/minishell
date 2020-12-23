#include "../includes/minishell.h"

void	free_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	fn(int sig)
{
	print_color_start(NULL, sig);
}

void	**make_copy_envp(t_all *all, char **envp)
{
	int i;
//	t_envp *temp;

	i = 0;
	all->envp = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i], 0);
		i++;
	}
	all->standart_fd[0] = dup(0);
	all->standart_fd[1] = dup(1);
	all->standart_fd[2] = dup(2);
	
	all->pipe = -1;
	all->fork = 0;
	all->status = 0;
	signal(SIGINT, &fn);
	signal(SIGQUIT, &fn);
	signal(SIGTSTP, &fn);
}

char	read_output_file(t_all *all, char sign)		// добавить ковычки
{	
	char	*file_name;
	char	c;
	int		result;

	file_name = NULL;

	//printf("SIGN = %c\n", sign);
	while (read(0, &c, 1))
		if (c != ' ')
			break;
	//file_name = str_plus_char(file_name, c);
	//result = read(0, &c, 1);
	if (c == '>')
	{
		sign = '2';
		result = read(0, &c, 1);
		while (c == ' ')
			result = read(0, &c, 1);
	}
	while (result)
	{
		if (c == '\n')
			break;
		else if (c == ' ' || c == ';' || c == '|')
			break;
		else if (c == '>' || c == '<')
			break;
		file_name = str_plus_char(file_name, c);
		result = read(0, &c, 1);
	}
	if (sign == '2')
	{
		all->output = open(file_name, O_CREAT | O_RDWR | O_APPEND);
		if (all->output == -1)
			printf("ERROR OPENNING\n");
	}
	if (sign == '>')
	{
		all->output = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		if (all->output == -1)
			printf("ERROR OPENNING\n");
	}
	else if (sign == '<')
	{
		//printf("%s\n", file_name);
		all->input = open(file_name, O_RDWR);	// изменить флаги открытия файла ??
		if (all->input == -1)
			printf("ERROR OPENNING\n");
	}
	return (c);
}

char	*read_array(char *flag_end_command, t_all *all)
{
	char	*array;
	char	c;
	char	result;
	int		i = 0;

	all->input = -1;
	all->output = -1;

	array = NULL;
	result = read(0, &c, 1);
//	printf("Im here\n");
	while (result)
	{
		//printf("C = \"%c\"\n", c);
		if (c == '\n')
		{
			*flag_end_command = 1;
			break;
		}
		else if (c == '\\')
		{
			result = read(0, &c, 1);
			if (result == 1)
			{
				array = str_plus_char(array, c);
				result = read(0, &c, 1);
				continue;
			}
			else
			{
				array = str_plus_char(array, '\0');
				break;
			}
		}
		else if (c == ';')
			break;
		else if (c == '|')
		{
			if (all->pipe == -1)
			{
				pipe(all->pipefd);
				all->pipe = 1;
			}
			if (all->pipe == 0)
			{
				pipe(all->pipefd_second);
				all->pipe = 2;	
			}
			break;
		}
		else if (c == '>' || c == '<')
		{
			c = read_output_file(all, c);
			continue;
		}
		array = str_plus_char(array, c);
		i++;
		result = read(0, &c, 1);
	}

	return(array);
}

int main (int argc, char **argv, char **envp)
{
    t_all	all;
	char	flag_end_command;
	char	*array;

	char	*command = "export";
	char	**arg[5];


	
	if (envp != NULL && envp[0] != NULL)	// Подумать над этим
		make_copy_envp(&all, envp);
	flag_end_command = 1;
/*
	command = "export";
	arg[0] = "export";
	arg[1] = "AAA=123";
	arg[2] = NULL;

	run_manager(&all, arg, command);

	command = "export";
	arg[0] = "export";
	arg[1] = NULL;

	run_manager(&all, arg, command);		

	command = "ls";
	arg[0] = "ls";
	arg[1] = NULL;

	run_manager(&all, arg, command);

	command = "env";
	arg[0] = "env";
	arg[1] = NULL;

	run_manager(&all, arg, command);

	command = "./a.out";
	arg[0] = "./a.out";
	arg[1] = NULL;	

	run_manager(&all, arg, command);

	command = "cd";
	arg[0] = "cd";
	arg[1] = "..";
	arg[2] = NULL;

	run_manager(&all, arg, command);

	command = "unset";
	arg[0] = "unset";
	arg[1] = "PWD";
	arg[2] = NULL;

	run_manager(&all, arg, command);

	command = "unset";
	arg[0] = "unset";
	arg[1] = "OLDPWD";
	arg[2] = NULL;

	run_manager(&all, arg, command);

	command = "cd";
	arg[0] = "cd";
	arg[1] = NULL;

	run_manager(&all, arg, command);

	command = "pwd";
	arg[0] = "pwd";
	arg[1] = NULL;

	run_manager(&all, arg, command);

	command = "export";
	arg[0] = NULL;
	arg[1] = NULL;

	run_manager(&all, arg, command);		

	command = "exit";
	arg[0] = "exit";
	arg[1] = "123";
	arg[2] = NULL;

	run_manager(&all, arg, command);*/

	all.output = -1;

	while (1)
	{
		//write(all.standart_fd[1], "WHHHHHAT\n", 10);
		if (flag_end_command == 1)
		{
			print_color_start(&all, 0);
			flag_end_command = 0;
		}

		array = read_array(&flag_end_command, &all);
//		printf("%s\n", array);
		if (all.pipe == 1)
		{
			if (all.input != -1)
				dup2(all.input, 0);
			
			if (all.output != -1)
				dup2(all.output, 1);
			else
				dup2(all.pipefd[1], 1);
		}
		else if (all.pipe == 0)
		{
			if (all.input != -1)
				dup2(all.input, 0);
			else
				dup2(all.pipefd[0], 0);
			
			if (all.output != -1)
				dup2(all.output, 1);
		}
		else if (all.pipe == 2)
		{
			if (all.input != -1)
				dup2(all.input, 0);
			else
				dup2(all.pipefd[0], 0);

			if (all.output != -1)
				dup2(all.output, 1);
			else
				dup2(all.pipefd_second[1], 1);
		}
		else if (all.pipe == -1)
		{
			if (all.input != -1)
				dup2(all.input, 0);
			if (all.output != -1)
				dup2(all.output, 1);
		}

		division_command(&all, array);
		
		if (all.pipe == 1)
		{
			all.pipe = 0;
			close(all.pipefd[1]);
		}
		else if (all.pipe == 0)
		{
			all.pipe = -1;
			close(all.pipefd[0]);
		}
		else if (all.pipe == 2)
		{
			close(all.pipefd[0]);

			dup2(all.pipefd_second[0], all.pipefd[0]);
			dup2(all.pipefd_second[1], all.pipefd[1]);
			close(all.pipefd[1]);
			close(all.pipefd_second[1]);
			all.pipe = 0;
		}

		dup2(all.standart_fd[0], 0);
		dup2(all.standart_fd[1], 1);
		dup2(all.standart_fd[2], 2);
		close(all.input);
		close(all.output);
		all.input = -1;
		all.output = -1;
	}
    return(0);
}