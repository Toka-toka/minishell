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
		write(1, name, ft_strlen(name));
	else
		write(1, "None", ft_strlen("None"));
}

void	print_color_start(t_all *all)
{
	write(1, "\033[1;31m", 7);			// Red
	write(1, "┌─[", 7);
	write(1, "\033[1;34m", 7);			// Blue
	print_used_or_dir(all, "NAME");					// Поправил печать имени пользователя
	write(1, "\033[1;31m", 7);			// Red
	write(1, "]-[", 3);
	write(1, "\033[1;34m", 7);			// Blue
	print_used_or_dir(all, "PWD");					// Поправил печать директории
	write(1, "\033[1;31m", 7);			// Red
	write(1, "]\n", 2);
	write(1, "└──╼ ", 14);
	write(1, "\033[1;33m", 7);			// Yellow
	write(1, "$", 1);
	write(1, "\033[0m", 4);				// Reset	
}