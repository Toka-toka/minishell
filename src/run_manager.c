#include "../includes/minishell.h"

char		*check_file(t_all *all, char *command)
{
	int		fd;
	DIR		*dirp;

	errno = 0;
	if ((fd = open(command, O_RDONLY)) != -1)
		close(fd);
	if (errno == 2)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		all->status = 127;
		return (NULL);
	}
	if (dirp = opendir(command))
	{
		closedir(dirp);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": is a directory\n", 2);
		all->status = 126;
		return (NULL);
	}
	return (ft_strdup(command));
}

int			our_command(char *command,
			void (**function)(t_all *all, char **arg))
{
	int		i;

	i = 1;
	if (ft_strcmp(command, "export") == 0)
		*function = ft_export;
	else if (ft_strcmp(command, "unset") == 0)
		*function = ft_unset;
	else if (ft_strcmp(command, "pwd") == 0)
		*function = ft_pwd;
	else if (ft_strcmp(command, "env") == 0)
		*function = ft_env;
	else if (ft_strcmp(command, "cd") == 0)
		*function = ft_cd;
	else if (ft_strcmp(command, "echo") == 0)
		*function = ft_echo;
	else if (ft_strcmp(command, "exit") == 0)
		*function = ft_exit;
	if (*function != NULL)
		i = 0;
	return (i);
}

void		run_manager(t_all *all, char **arg, char *command)
{
	void	(*function)(t_all *all, char **arg);
	char	*path;

	all->status = 0;
	function = NULL;
	if (command[0] == '.' || command[0] == '/')
		path = check_file(all, command);
	else if (our_command(command, &function) == 0)
		path = NULL;
	else
		check_way(all, command, &path);
	if (function != NULL && all->pipe == -1)
		function(all, arg);
	else if ((function != NULL && all->pipe > -1) || path != NULL)
		fork_create(all, path, arg, function);
	if (path != NULL)
		free(path);
}

void		division_command(t_all *all, char *array)
{
	char	*command;
	char	*way;
	char	**arg;
	int		i;

	i = 0;
	command = NULL;
	if (array == NULL)
		return ;
	read_word(all, array, &command, i);
	arg = read_arg(all, array, &i);
	run_manager(all, arg, command);
}
