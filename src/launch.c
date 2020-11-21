#include "../includes/minishell.h"

char     *find_command(t_all *all, char *command)
{
    char    **path;
    char    *way;
    int     i;
	DIR 	*dirp;
    
    i = 0;
    path = ft_split(search_var(all, "PATH"), ':');
    while (path[i] != NULL)
    {
        way = ft_strjoin(path[i], "/");
        way = ft_strjoin(way, command);
        if (open(way, O_RDONLY) != -1)
            return(way);
        i++;
    }
   if (open(command, O_RDONLY) != -1)
    {
		if (dirp = opendir(command));
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": is a directory\n", 2);
			all->status = 126;
			return (NULL);
		}
        return(command);
    }
//  ft_putstr_fd(strerror(errno), 2);
//  ft_putstr_fd("\n", 2);
    return (NULL); // не нашлось 
}

void	division_command(t_all *all, char *array)
{
	char	*command;
    char    *way;
	char	**arg;
	int		i;

	i = 0;				// Не работает с | и ;     определить хранение индекса
	command = NULL;
	if (array == NULL)
		return ;
	read_word(array, &command, i);
	arg = read_arg(array, &i);

	if (check_our_command(all, arg, command) == 0) //&& (way = find_command(all, command)) != NULL)
	{
		pid_t	pid;
		int		status;

//		command = ft_strjoin("/bin/", command);
		pid = fork();
		if (pid == 0)
		{
			if(strcmp(arg[0], "exit") == 0)
				ft_exit(all, arg);
			else if ((execve(way, arg, arr_from_list(all))) == -1)	// Завершение процессов после неправильного выполнения
			{	
				printf("pid = %d\n", pid);
				printf("errno = %d, error = %s\n", errno, strerror(errno)); // вытащил ошибку просто интереса ради
			}
		}
//		ft_exit(all, arg);
		wait (&status);
		printf("all->status (fork)= %d", all->status);
//		if (WIFEXITED(status))
//		{
//        	all->status = WEXITSTATUS(status);
//		}
	}
}
