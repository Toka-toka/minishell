#include "../includes/minishell.h"

void	fork_create(t_all *all, char *path, char **arg, void (*function)(t_all *all, char **arg))
{
	pid_t	pid;
	int		status;
	char	**envp;
	
	errno = 0;
	pid = fork();
	
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
		all->status = WEXITSTATUS(status);
//		free_arr((void**)envp);
	}
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

void	division_command(t_all *all, char *array)
{
	char	*command;
    char    *way;
	char	**arg;
	int		i;

	i = 0;
	command = NULL;
	if (array == NULL)
		return ;
	read_word(array, &command, i);
	arg = read_arg(array, &i);
	run_manager(all, arg, command);
}