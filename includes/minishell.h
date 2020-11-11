#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

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

void    add_var(t_all *all, const char *str);

#endif