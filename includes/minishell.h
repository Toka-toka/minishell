/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 06:33:20 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:11:23 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>

typedef struct		s_envp
{
	char			*name;
	char			*value;
	char			prinf_flag;
	struct s_envp	*next;
}					t_envp;

typedef struct		s_all
{
	char			pipe;
	char			input;
	char			output;
	int				pipefd[2];
	int				pipefd_second[2];
	char			fork;
	int				standart_fd[2];
	t_envp			*envp;
	unsigned char	status;
}					t_all;

void				ft_putstr(char *str);
void				add_var(t_all *all, const char *str);
void				print_envp(t_all *all, int i);
char				**arr_from_list(t_all *all);
char				*search_var(t_all *all, char *name);
void				del_var(t_all *all, char *name);
void				print_sort(t_all *all);
void				print_err(char *function, char *arg, char *err);
void				ft_unset(t_all *all, char **arg);
void				ft_env(t_all *all, char **arg);
void				ft_export(t_all *all, char **arg);
void				ft_pwd(t_all *all, char **arg);
void				ft_cd(t_all *all, char **arg);
void				ft_echo(t_all *all, char **arg);
void				ft_exit(t_all *all, char **arg);
void				free_arr(void **arr);
void				fork_create(t_all *all, char *path, char **arg,
void				(*function)(t_all *all, char **arg));
void				check_way(t_all *all, char *command, char **path);
void				critical_error(char *function, char *arg, char *err);
void				run_manager(t_all *all, char **arg);
int					var_name_check(char *name, int j);
void				print_color_start(t_all *all, int sig);
char				*read_array(char *flag_end_command, t_all *all);
int					read_word(t_all *all, char *array, char **command, int i);
char				**read_arg(t_all *all, char *array, int *i);
char				check_our_command(t_all *all, char **arg, char *command);
void				division_command(t_all *all, char *array);
char				*str_plus_char(char *src, char c);
char				print_error(char *error_str, char *sumbol);
void				free_arg(char **arg);
char				*str_plus_str(char *src, char *dest);
char				*number_to_str(char *command, int status);
char				find_error(char *str_input);
void				fn(int sig);
void				make_copy_envp(t_all *all, char **envp);
int					read_for_echo(t_all *all, char *array,
									char **command, int *i);
char				redirect_file(t_all *all, int *i, char *str);

#endif
