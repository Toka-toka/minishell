#include "../includes/minishell.h"

char     *find_command(t_all *all, char *command)
{
    char    **path;
    char    *way;
    int     i;
    
    i = 0;
    path = ft_split(search_var(all, "PATH"), ':');
    while (path[i] != NULL)
    {
        printf("path[i] = %s\n", path[i]);
        way = ft_strjoin(path[i], "/");
        way = ft_strjoin(way, command);
        printf("way = %s\n", way);
        if (open(way, O_RDONLY) != -1)
            return(way);
        i++;
    }
    if (open(command, O_RDONLY) != -1)
    {
        printf("this way = %s\n", command);
        return(command);
    }
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
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

	if (check_our_command(all, arg, command) == 0 && (way = find_command(all, command)) != NULL)
	{
		pid_t	pid;
		int		status;

//		command = ft_strjoin("/bin/", command);
		pid = fork();
		if (pid == 0)
		{
			if ((execve(way, arg, arr_from_list(all))) == -1)	// Завершение процессов после неправильного выполнения
			{	
				printf("pid = %d\n", pid);
				printf("errno = %d, error = %s\n", errno, strerror(errno)); // вытащил ошибку просто интереса ради
			}
		}
		wait(&status);
		if (WIFEXITED(status))
		{
        	printf("Exit status: %d\n", WEXITSTATUS(status));
			printf("error = %s\n", strerror(status));
		}
	}

}
