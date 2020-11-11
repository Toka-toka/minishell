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

void division_command(char *array)
{
	char	*command;
	char	*arg;
	int		i;

	command = NULL;
	arg = NULL;
	i = 0;
	if (array == NULL)
	{
		printf("Command = NULL\n");
		return ;
	}
	while (array[i] == ' ')
		i++;
	while (array[i] != '\0' && array[i] != ' ')
	{
		command = str_plus_char(command, array[i]);
		i++;
	}
	printf("Command = %s\n", command);
}

int main (int argc, char **argv, char **envp)
{
	/*
    int		i = 0;
    char	*path;

    path = NULL;
    path = getcwd(NULL, 0);
    printf("path = %s\n", path);
    free(path);
    while (envp[i] != NULL)
    {
        printf("envp[%d] = %s\n", i, envp[i]);l
        i++;
    }
    */
	char	*array;
	char	c;

	while (1)
	{
		print_start_command();
		array = read_array();
		division_command(array);
		//printf("command = %s\n", array);
		free(array);
	}

	/*
	printf("\n\n");
	char	command[BUFSIZ];
	int		status;
	pid_t	pid;
	
	while (1)
	{
		printf("simpsh:  ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			return (0);
		}

		char	**str = (char **)malloc(4 * 8);
		str[0] = "ls";
		str[1] = "-l";
		str[2] = "AAA 123";
		str[2] = NULL;
	
		command[strlen(command) - 1] = '\0';
		if ((pid = fork()) == 0)
			execve("/bin", str, envp);
		
		while(wait(&status) != pid)
			continue;
		
		printf("\n");
	}
	*/

    return(0);
}