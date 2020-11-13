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

void	print_start_command(void)
{
	write(1, "\033[1;31m", 7);	// RED
	write(1, "┌─[", 7);
	write(1, "\033[1;34m", 7);	// BLUE
	write(1, "toka-toka", 9);
	write(1, "\033[1;31m", 7);	// RED
	write(1, "]─[pwd]\n", 10);
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

void division_command(char *array)
{
	char	*command;
	char	*arg;
	int		i;

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


	// EXPORT
	if (strcmp(command, "export") == 0)
	{
		printf("This is your export command\n");
	}
	// UNSET
	else if (strcmp(command, "unset") == 0)
	{
		printf("This is your unset command\n");
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