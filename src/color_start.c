#include "../includes/minishell.h"

/*
	По-факту оставил твой код, лишь убрал лишние переменные и засуну все в одну функцию,
	т.к. действие выполниют одно.
*/
void	print_used_or_dir(t_all *all, char *src)
{
	char	*name;

	name = search_var(all, src);
	if (name != NULL)
		write(0, name, ft_strlen(name));
	else
		write(0, "None", ft_strlen("None"));
}

void	print_color_start(t_all *all, int sig)
{
	static	t_all *temp;

	if (temp == NULL)
		temp = all;
	if (sig != 0)
		write(0, "\n", 1);
	if (temp->fork == 0 && sig != SIGQUIT)
	{
		write(0, "\033[1;31m", 7);			// Red
		write(0, "┌─[", 7);
		write(0, "\033[1;34m", 7);			// Blue
		print_used_or_dir(temp, "USERNAME");					// Поправил печать имени пользователя
		write(0, "\033[1;31m", 7);			// Red
		write(0, "]-[", 3);
		write(0, "\033[1;34m", 7);			// Blue
		print_used_or_dir(temp, "PWD");					// Поправил печать директории
		write(0, "\033[1;31m", 7);			// Red
		write(0, "]\n", 2);
		write(0, "└──╼ ", 14);
		write(0, "\033[1;33m", 7);			// Yellow
		write(0, "$", 1);
		write(0, "\033[0m", 4);				// Reset
	}
	if (sig == SIGINT)
		temp->status = 130;
}