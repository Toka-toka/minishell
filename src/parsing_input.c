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

/*
	Функция чтения слова / слов в ковычках. Сохраняет аргумент в **command.
	Возвращает индекс текущего элемента.
*/
int		read_word(char *array, char **command, int i)
{
	char	quote_flag;			// Если найдена ковычка = 1

	quote_flag = 0;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	while (array[i] != '\0')
	{
		if (array[i] == '\"')
		{
			quote_flag = !quote_flag;
			i++;
			continue;
		}
		else if (array[i] == ' ' && quote_flag == 0)
		{
			if (*command == NULL)
				*command = str_plus_char(NULL, '\0');
			break;
		}
		*command = str_plus_char(*command, array[i]);
		i++;
	}
	return (i);
}

/*
	Функция подсчета количества аргументов для двумерного массива
*/
int		number_word(char *array, int i)
{
	char	word_flag;	// Флаг детекта конца слова, определяется по пробелам
	char	arg_flag;	// Флаг конца ковычки, восстанавливается по второй ковычке
	int		number;		// Длина двумерного массива

	word_flag = 1;
	arg_flag = 0;
	number = 0;
	while (array[i] != '\0' && array[i] != ';' && array[i] != '|')
	{
		if (array[i] == '\"')
			arg_flag = !arg_flag;
		if (array[i] != ' ' && arg_flag != 1)
		{
			if (word_flag != 0)
				number += 1;
			word_flag = 0;
		}
		else
			word_flag = 1;
		i++;
	}
	//printf("ALL NUMBER ARG = %d\n", number);
	return (number);
}

/*
	Сохранение переданной строки в двумерный массив по аргументам.
*/
char	**read_arg(char *array, int *i)
{
	char	**arg;
	int		len;
	int		j;

	len = number_word(array, *i);					// Не работает с | и ;
	arg = (char **)malloc((len + 1) * sizeof(char *));
	if (arg == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{	
		arg[j] = NULL;
		*i = read_word(array, &arg[j], *i);
		j++;
	}
	arg[j] = NULL;
	return (arg);
}

char	check_our_command(t_all *all, char **arg, char *command)
{
	char	result;

	result = 1;
	if (strcmp(command, "export") == 0)
		ft_export(all, arg);
	else if (strcmp(command, "unset") == 0)
		ft_unset(all, arg); 
	else if (strcmp(command, "pwd") == 0)
		ft_pwd(all, arg);
	else if (strcmp(command, "env") == 0)
		ft_env(all, arg);
	else if (strcmp(command, "cd") == 0)
		ft_cd(all, arg);
	else
		result = 0;
	return (result);
}

void	division_command(t_all *all, char *array)
{
	char	*command;
	char	**arg;
	int		i;

	i = 0;				// Не работает с | и ;     определить хранение индекса
	command = NULL;
	if (array == NULL)
		return ;
	read_word(array, &command, i);
	arg = read_arg(array, &i);

	if (check_our_command(all, arg, command) == 0)
	{
		pid_t	pid;				//		[!!!]	!!!!	[!!!]
		int		status;				//		РАЗОБРАТЬСЯ С СОЗДАНИЕМ ПРОЦЕССА
									//		ВОЗРАЩАЕМЫМ ЗНАЧЕНИЕМ
									//		ЗАВЕРШЕНИЕМ ПРОЦЕССА
									//		[!!!]	!!!!	[!!!]

		command = ft_strjoin("/bin/", command);		// Добавить перебор путей
		if ((pid = fork()) == 0)
			if ((execve(command, arg, 0)) == -1)	// Завершение процессов после неправильного выполнения
				return ;

		while(wait(&status) != pid)
				continue;
	}
}