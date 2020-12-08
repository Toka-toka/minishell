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

char	*number_to_str(char *command, int status, t_all *all)
{
	int		i;
	int		number;

	i = 1;
	number = status;
//	dprintf(all->standart_fd[1], "status = %d\n", status);
	while (number > 9)
	{
		i++;
		number = number / 10;
	}
	number = 1;
	while (i > 1)
	{
		number *= 10;
		i -= 1;
	}
//	dprintf(all->standart_fd[1], "number = %d\n", number);
	while (number != 0)
	{
		command = str_plus_char(command, status / number + 48);
		status = status % number;
		number = number / 10;
	}
//	dprintf(all->standart_fd[1], "str = %s\n", str);
	return (command);
}

/*
	Функция чтения слова / слов в ковычках. Сохраняет аргумент в **command.
	Возвращает индекс текущего элемента.
*/
int		read_word(t_all *all, char *array, char **command, int i)
{
	char	quote_flag;			// Если найдена ковычка = 1
	char	single_quote_flag;
	char	c;

	quote_flag = 0;
	single_quote_flag = 0;
	while (array[i] == ' ' || array[i] == '\t')
		i++;
	while (array[i] != '\0')
	{
		if (array[i] == '\'' || single_quote_flag == 1)
		{
			//dprintf(all->standart_fd[1], "single_quote_flag = \"%d\"\n", single_quote_flag);
			if (array[i] == '\'')
			{
				single_quote_flag = !single_quote_flag;
			}
			else
				*command = str_plus_char(*command, array[i]);
			i += 1;
			continue;
		}
		else if (array[i] == '$')
    	{
	      if (array[i + 1] == '?')
	      {
	        printf("status = %d\n", all->status);
			*command = number_to_str(*command, all->status, all);
	        i += 2;
	        continue;
      }
		else
		{
			char  *name;
			int    j;

			name = NULL;
			j = i + 1;
			write(all->standart_fd[1], "TEST\n", 5);
			while (ft_isalnum(array[j]))
			{
			name = str_plus_char(name, array[j]);
			j++;
			if (name[0] >= '0' && name[0] <= '9')
			{
				i = j;
				continue;
			}
			
			}
			//read_word(all, array, &name, j);
//			dprintf(all->standart_fd[1], "name = \"%s\"\n", name);
			if (name != NULL)
			{
			char  *str;
			str = search_var(all, name);
			if (*command == NULL)
				*command = ft_strjoin("", search_var(all, name));
			else
				*command = ft_strjoin(*command, search_var(all, name));
//			dprintf(all->standart_fd[1], "str = \"%s\"\n", *command);
			
			}
			if (array[j] == '$' && i != j)
			{
			i = j;
			continue;
			}
			if (array[j] != ' ' && array[j] != '\0')
			{
//			dprintf(all->standart_fd[1], "array[j] = \"%c\"\n", array[j]);
			i = j;
			continue;
			//i -= 1;
			}
			else
			i = j;
		}
		}
		else if (array[i] == '\"')
		{
			quote_flag = !quote_flag;
			i++;
			continue;
		}
/*		else if (array[i] == '\\')
		{
			if (array[i + 1] != '\0')
			{
				*command = str_plus_char(*command, array[i + 1]);
				i += 2;
			}
			else
			{
				while (read(all->standart_fd[1], &c, 1))
				{
					if (c == '\n')
						break;
					*command = str_plus_char(*command, c);
					i += 1;

				}
			}
			//i += 2;
			continue;
		} */
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
	char	slash;

	word_flag = 1;
	arg_flag = 0;
	number = 0;
	while (array[i] != '\0' && array[i] != ';' && array[i] != '|')
	{
		if (array[i] == '\"')
			arg_flag = !arg_flag;
		//if 
		if (array[i] != ' ' && arg_flag != 1)
		{
			if (word_flag != 0)
				number += 1;
			//word_flag = 0;
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
char	**read_arg(t_all *all, char *array, int *i)
{
	char	**arg;
	int		len;
	int		j;

	len = number_word(array, *i);					// Не работает с | и ;
	arg = (char **)malloc((len + 1) * sizeof(char *));
//	dprintf(all->standart_fd[1], "LEn = %d", len);
	if (arg == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{	
		arg[j] = NULL;
		*i = read_word(all, array, &arg[j], *i);
	//	dprintf(all->standart_fd[1], "ARG = \"%s\"\n", arg[j]);
		j++;
	}
	arg[j] = NULL;
	return (arg);
}
