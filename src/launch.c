#include "../includes/minishell.h"

char    **arr_from_list(t_all *all) // создание массива из списка
{
    t_envp  *current;
    char    **arr;
    char    *temp;
    int     i;

    //printf("all = %p\n", all);
    i = 0;
    current = all->envp;
    while (current != NULL)
    {
        current = current->next;
        i++;
    }
    arr = (char **)malloc(sizeof(char *) * (i));
    current = all->envp;
    i = 0;
    while (current != NULL)
    {
        temp = ft_strjoin(current->name, "=");
        arr[i] = ft_strjoin(temp, current->value);
        i++;
        current = current->next;
    }
    arr[i] = NULL;
    return(arr);
}

void	fork_create(t_all *all, char *path, char **arg, void (*function)(t_all *all, char **arg))
{
	pid_t	pid;
	int		status;
	char	**envp;
	
	errno = 0;

	pid = fork();
	all->fork = 1;
	if (pid == 0)
	{
		if(function != NULL)
		{
			function(all, arg);
			exit(all->status);
		}
		envp = arr_from_list(all);
		if(execve(path, arg, envp) == -1)
		{	
			if (errno == 13)
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				exit (126);
			}
			ft_putstr_fd("Execve return -1, exit code = errno\n", 2);
			exit(errno);
		}
	}
	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			all->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			all->status = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			all->status = 128 + WSTOPSIG(status);
		all->fork = 0;
//		free_arr((void**)envp);
	}
	pid = -1;
}

char	*ckeck_file(t_all *all, char *command)
{
	int fd;
	DIR *dirp;
	
	errno = 0;
	if ((fd = open(command, O_RDONLY)) != -1)
		close(fd);
	if (errno == 2)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		all->status = 127;
		return(NULL);
	}
	if (dirp = opendir(command))
	{
		closedir(dirp);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": is a directory\n", 2);
		all->status = 126;
		return(NULL);
	}	
	return(command);
}

// проверка открытия файла из PATH

char     *ckeck_way(t_all *all, char *command)
{
	char	**all_path;
	char	*path;
	int		i;
	int		fd;
	DIR		*dirp;
    
	i = 0;
	all_path = ft_split(search_var(all, "PATH"), ':');
	if (all_path == NULL)
	{
		all_path = malloc(sizeof(char*) * 2);
		all_path[0] = getcwd(NULL, 0);
		all_path[1] = NULL;
	}
	errno = 2;
    while (all_path[i] != NULL && errno == 2)
    {
		path = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(path, command);
		if ((fd = open(path, O_RDONLY)) != -1)
		{
			errno = 0;
			close(fd);
		}
		i++;
    }
	dirp = NULL;
	if (errno == 2 || (dirp = opendir(path)) != NULL)
	{
		if (dirp != NULL)
			closedir(dirp);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		all->status = 127;
		return(NULL);
	}
	return(path);
}

void	run_manager(t_all *all, char **arg, char *command)
{
	void	(*function)(t_all *all, char **arg);
	char	*path;

	function = NULL;
	path = NULL;

	all->status = 0;
	if (command [0] == '.' || command[0] == '/')
		path = ckeck_file(all, command);
	else if (strcmp(command, "export") == 0)
		function = ft_export;
	else if (strcmp(command, "unset") == 0)
		function = ft_unset; 
	else if (strcmp(command, "pwd") == 0)
		function = ft_pwd;
	else if (strcmp(command, "env") == 0)
		function = ft_env;
	else if (strcmp(command, "cd") == 0)
		function = ft_cd;
	else if (strcmp(command, "echo") == 0)
		function = ft_echo;
	else if (strcmp(command, "exit") == 0)
	   function = ft_exit;
	else
		path = ckeck_way(all, command);
	if (function != NULL && all->pipe == -1)
		function(all, arg);
	else if ((function != NULL && all->pipe > -1) || path != NULL)
		fork_create(all, path, arg, function);
}

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

	//command = echo;
	
	output_fd = all->standart_fd[1];
	input_fd = all->standart_fd[0];
	//printf("!!!!!\n");
	pipe_before_command(all, &output_fd, &input_fd);
	dup2(output_fd, 1);
	dup2(input_fd, 0);
	run_manager(all, arg, command);
	pipe_after_command(all);
}