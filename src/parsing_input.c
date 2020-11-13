#include "../includes/minishell.h"

char	*str_plus_char(char *src, char c)
{
	char	*dest;
	int		i;

	i = 0;
	if (src != NULL)
	{
		if ((dest = (char *)malloc(ft_strlen(src) + 2)) == NULL)
			return (NULL);
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
		if ((dest = (char *)malloc(2)) == NULL)
			return (NULL);
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}


char	*read_array(void)
{
	char	*array;
	char	c;

	array = NULL;
	while (read(0, &c, 1))
	{
		
		array = str_plus_char(array, c);
		if (c == '\n'|| c == '|' || c == ';')
			break;
	}
	return(array);
}

void	print_start_command(t_all *all)
{
	int len;
	char	*name;
	char	*pwd;
	
	write(1, "\033[1;31m", 7);	// RED
	write(1, "┌─[", 7);
	write(1, "\033[1;34m", 7);	// BLUE
	name = search_var(all, "NAME");
	if (name != NULL)
		len = ft_strlen(name);
	else
	{
		name = "None";
		len = 4;
	}
	write(1, name, len);
	write(1, "\033[1;31m", 7);	// RED
	pwd = search_var(all, "PWD");
	if (pwd != NULL)
		len = ft_strlen(pwd);
	else
	{
		pwd = "None";
		len = 4;
	}
	write(1, "][", 2);
	write(1, pwd, len);
	write(1, "]\n", 2);
	write(1, "└──╼ ", 14);
	write(1, "\033[1;33m", 7);	// YELLOW
	write(1, "$", 1);
	write(1, "\033[0m", 4);		// Reset	
}

int		read_word(char *array, char **command)
{
	int		i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] == ' ')
		i++;
	while (array[i] != '\0' && array[i] != ' ' && array[i] != '\n')
	{
		*command = str_plus_char(*command, array[i]);
		i++;
	}
	return (i);
}

void	number_word(char *array, int i)
{
	char	word_flag;
	char	arg_flag;
	int		number;

	word_flag = 0;
	arg_flag = 0;
	number = 0;
	while (array[i] != '\0')
	{
		if (array[i] != ' ')
		{
			if (word_flag != 0)
				number += 1;
			word_flag = 0;
		}
		else
			word_flag = 1;
		i++;
	}
	printf("ALL NUMBER = %d\n", number);
}

void division_command(t_all *all, char *array)
{
	char	*command;
	char	*arg;
	int		i;
	char	*args[4]; // добавил для аргументов

	command = NULL;
	arg = NULL;
	i = read_word(array, &command);
	if (i == 0)
		return ;
	number_word(array, i);
	

	while (array[i] != '\0')
	{
		arg = str_plus_char(arg, array[i]);
		i++;
	}
	printf("Command = %s\n", command);
	if (arg == NULL)
		printf("Arg = NULL\n");
	else
		printf("Arg = %s\n", arg);

	if (strcmp(command, "env") == 0)
	{
		arg = ft_strjoin("env ", arg);
		ft_env(all,  ft_split(arg, ' '));
	}
	// EXPORT
	if (strcmp(command, "export") == 0)
	{
		args[0] = "export"; // добавил чтобы появились аргументы
		args[1] = "NAME=123";
		args[2] = "PWD=456";
		args[3] = NULL;
		ft_export(all, args);
	}
	// UNSET
	else if (strcmp(command, "unset") == 0)
	{
		args[0] = "unset"; // добавил чтобы появились аргументы
		args[1] = "NAME";
		args[2] = "PWD";
		args[3] = NULL;

		ft_unset(all, args); 
	}
	else
	{
		pid_t	pid;
		int		status;
		
		char	**str = (char **)malloc(4 * 8);
		str[0] = "\0";	// Добавить добавление аргументов в двумерный массив
		str[1] = NULL;

		
		command = ft_strjoin("/bin/", command);
		printf("\"%s\"\n", command);
		if ((pid = fork()) == 0)
			if ((execve(command, str, 0)) == -1)	// Завершение процессов после неправильного выполнения
				return ;

		while(wait(&status) != pid)
				continue;
		

		free(str);
	}
}