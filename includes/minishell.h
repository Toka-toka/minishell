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
#include <dirent.h>
#include <sys/types.h>

//int		signal_flag;
//pid_t	pid;

typedef struct      s_envp
{
    char            *name;
    char            *value;
    char            *prinf_flag;
    struct s_envp   *next;
}                   t_envp;

typedef struct      s_all
{
    char	pipe;               // Флаг для |
	char	input;              // Флаг для <
	char	output;             // Флаг для >
    int     pipefd[2];          // Файловые дексрипторы для |
    int     pipefd_second[2];
    char    fork;               // Флаг для дочерних процессов
    int     standart_fd[3];     // stdinput, stdout, stderr
    t_envp          *envp;
    unsigned char   status;
}                   t_all;

void	ft_putstr(char *str);
void    add_var(t_all *all, const char *str, int i);
void    print_envp(t_all *all, int i);
char    **arr_from_list(t_all *all);
char    *search_var(t_all *all, char *name);
void    del_var(t_all *all, char *name);
void    print_sort(t_all *all);
void	print_err(char *function, char *arg, char *err);
void    ft_unset(t_all *all, char **arg);
void    ft_env(t_all *all, char **arg);
void    ft_export(t_all *all, char **arg);
void    ft_pwd(t_all *all, char **arg);
void    ft_cd(t_all *all, char **arg);
void    ft_echo(t_all *all, char **arg);
void    ft_exit(t_all *all, char **arg);
void	free_arr(void **arr);
void	fork_create(t_all *all, char *path, char **arg,
        void (*function)(t_all *all, char **arg));
void	*check_way(t_all *all, char *command, char **path);
void		critical_error(char *function, char *arg, char *err);

void	print_color_start(t_all *all, int sig);
char	*read_array(char *flag_end_command, t_all *all);
int     read_word(t_all *all, char *array, char **command, int i);
char    **read_arg(t_all *all, char *array, int *i);
char	check_our_command(t_all *all, char **arg, char *command);
void    division_command(t_all *all, char *array);
char	*str_plus_char(char *src, char c);

#endif