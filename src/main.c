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

void	**make_copy_envp(t_all *all, char **envp)
{
	int i;
//	t_envp *temp;

	i = 0;
	all->envp = NULL;
	while (envp[i] != NULL)
	{
		add_var(all, envp[i]);
		i++;
	}
}
/*
char	*read_array(char *flag_end_command)
{
	char	*array;
	char	c;

	array = NULL;
	while (read(0, &c, 1))
	{
		if (c == '\n')
		{
			*flag_end_command = 1;
			break;
		}
		else if (c == ';')
			break;
		array = str_plus_char(array, c);
		if (c == '|' )
			break;
	}
	return(array);
}
*/

char	read_output_file(t_all *all, char sign)
{
	char	*file_name;
	char	c;

	file_name = NULL;

	//printf("SIGN = %c\n", sign);
	while (read(0, &c, 1))
		if (c != ' ')
			break;
	file_name = str_plus_char(file_name, c);
	while (read(0, &c, 1))
	{
		if (c == '\n')
			break;
		else if (c == ' ' || c == ';' || c == '|')
			break;
		else if (c == '>' || c == '<')
			break;
		file_name = str_plus_char(file_name, c);
	}
	if (sign == '>')
	{
		all->output = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		if (all->output != -1)
			dup2(all->output, 1);
		all->output = -1;
	}
	else if (sign == '<')
	{
		all->input = open(file_name, O_RDWR);	// изменить флаги открытия файла ??
		if (all->input != -1)
			dup2(all->input, 0);
		all->input = -1;
	}
	//printf("file_name = %s\n", file_name);
	return (c);
}

char	*read_array(char *flag_end_command, t_all *all)
{
	char	*array;
	char	c;
	char	result;
	int		i = 0;

	//all->pipe = -1;
	all->input = -1;
	all->output = -1;

	array = NULL;
	result = read(0, &c, 1);
	while (result)
	{
		if (c == '\n')
		{
			*flag_end_command = 1;
			break;
		}
		else if (c == ';')
			break;
		else if (c == '|')
		{
			if (all->output == -1)
				all->pipe = i;
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
	/*
	printf("first_pipe %d\n", all->pipe);
	printf("re_input %d\n", all->input);
	printf("re_output %d\n", all->output);
	printf("ARRAY = %s\n", array);
	*/
	return(array);
}

void	fn(int sig)
{
	char	*message;

	message = "Do nothing";
	ft_putchar_fd('\n', 1);
}

int main (int argc, char **argv, char **envp)
{
    t_all	all;
	char	flag_end_command;
	char	*array;
	
	if (envp != NULL && envp[0] != NULL)	// Подумать над этим
		make_copy_envp(&all, envp);
	flag_end_command = 1;
	

	//all.output = -1;
	all.standart_fd[0] = dup(0);
	all.standart_fd[1] = dup(1);
	all.standart_fd[2] = dup(2);
	
	all.pipe = -1;
	signal(SIGINT, fn);
	signal(SIGQUIT, fn);
	while (1)
	{

		//write(all.standart_fd[1], "WHHHHHAT\n", 10);
		if (flag_end_command == 1)
		{
			print_color_start(&all);
			flag_end_command = 0;
		}
		array = read_array(&flag_end_command, &all);

		if (all.pipe > 0)
		{
			if (pipe(all.pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			//printf("Find pipe\n");
			dup2(all.pipefd[0], 0);
			dup2(all.pipefd[1], 1);
		}
		else if (all.pipe == 0)
		{
			close(all.pipefd[1]);
			dup2(all.pipefd[0], 0);
			
			//dup2(all.standart_fd[1], 1);

			//char c;
			//while (read(all.pipefd[0], &c, 1))
			//	write(1, &c, 1);
			//close(0);
			//printf("!!!\n");
			//dup2(all.standart_fd[0], 0);
		}
		//printf("ARRAY = %s\n", array);
		division_command(&all, array);
//		free(array);

		//char c;
		//while (read(0, &c, 1))
		//	write(all.standart_fd[1], &c, 1);

		if (all.pipe > 0)
		{
			//dup2(all.pipefd[1], 0);
			//dup2(all.standart_fd[1], 1);
			all.pipe = 0;
			close(0);
			//close(all.pipefd[1]);
		}
		else if (all.pipe == 0)
		{
			
			all.pipe = -1;
		}
		dup2(all.standart_fd[0], 0);
		dup2(all.standart_fd[1], 1);
		dup2(all.standart_fd[2], 2);
	}
    return(0);
}