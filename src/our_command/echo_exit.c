#include "../../includes/minishell.h"

void    ft_echo(t_all *all, char **arg) // -n!
{
    int i;
    char    n_flag;
    
    i = 1;
    n_flag = 0;
    while (arg[i] != NULL && strcmp(arg[i], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }
    while (arg[i] != NULL)
    {
        ft_putstr_fd(arg[i], 1);
        i++;
        if (arg[i] != NULL)
            ft_putstr_fd(" ", 1);
    }
    if (n_flag == 0)
        ft_putstr_fd("\n", 1);
    all->status = 0;
}

int    ckeck_exit_arg(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return(1);
        i++;
    }
    return(0);
}

void    ft_exit(t_all *all, char **arg)
{  
    unsigned char status;
    int i;
    
    i = 0;
    if (arg[1] == NULL)
        status = 0;
    else if(arg [1] != NULL && (ckeck_exit_arg(arg[1]) == 1))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(arg[1], 2);
        ft_putstr_fd(": требуется числовой аргумент\n", 2);
        status = 2;
    }
    else if (arg[2] != NULL)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        status = 1;
    }
    else
        status = ft_atoi(arg[1]);
    if (all->pipe == -1)
    {
//        del_var(all, NULL);
        exit(status);
    }
    else 
        all->status = status;
}