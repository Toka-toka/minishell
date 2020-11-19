#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

typedef struct      s_envp
{
    char            *name;
    char            *value;
    struct s_envp   *next;
}                   t_envp;

typedef struct      s_all
{
    t_envp         *envp;
}                   t_all;

void	ft_putstr(char *str);
void    add_var(t_all *all, const char *str);
void    print_envp(t_all *all, int i);
char    **arr_from_list(t_all *all);
char    *search_var(t_all *all, char *name);
void    del_var(t_all *all, char *name);
void    ft_unset(t_all *all, char **arg);
void    ft_env(t_all *all, char **arg);
void    ft_export(t_all *all, char **arg);
void    ft_pwd(t_all *all, char **arg);
void    ft_cd(t_all *all, char **arg);

void	print_color_start(t_all *all);
char	*read_array(char *flag_end_command);
int		read_word(char *array, char **command, int i);
char	**read_arg(char *array, int *i);
char	check_our_command(t_all *all, char **arg, char *command);
void    division_command(t_all *all, char *array);
char	*str_plus_char(char *src, char c);

#endif