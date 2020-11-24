#include "../includes/minishell.h"

int     var_name_check(char *name, int j) // j = 0 для unset и j = 1 для export
{
    int i;

    i = 0;
    if (ft_isdigit(name[0]) != 0)
        return(1);
    while (name[i] != '\0' && name[i] != '=')
    {
        if (ft_isalnum(name[i]) == 0 && name[i] != '_')
            return(1);
        i++;
    }
    if (j == 0 && name[i] == '=')
        return(1);
    return(0); // 
}

void    ft_export(t_all *all, char **arg)
{
    int i;
    
    i = 0;
    if (arg[1] == NULL)
        print_envp(all, 1);
    else
    {
        while (arg[i] != NULL)
        {
            if ((all->status = var_name_check(arg[i], 1)) == 1)
            {
                ft_putstr_fd("export: ", 2); // куда нужно направлять ошибки...?
                ft_putstr_fd(arg[i], 2);
                ft_putstr_fd(": not a valid identifier\n", 2);
            }
            else
                add_var(all, arg[i]);
            i++;
        }
    }
}

void    ft_unset(t_all *all, char **arg)
{
    int i;
    
    i = 1;
    if (arg != NULL && arg[0] != NULL && arg[1] != NULL)
    {
        while (arg[i] != NULL)
        {
            if ((all->status = var_name_check(arg[i], 0)) == 1)
            {
                ft_putstr_fd("unset: ", 2); // куда нужно направлять ошибки...?
                ft_putstr_fd(arg[i], 2);
                ft_putstr_fd(": not a valid identifier\n", 2);
            }
            else
                del_var(all, arg[i]);
            i++;
        }
    }
}

void    ft_env(t_all *all, char **arg)
{
    int i = 0;
    
    if (arg[1] != NULL)
    {
        ft_putstr("env: works only without arguments\n");
        all->status = 1;
    }
    else
    {
        print_envp(all, 0);
        all->status = 0;
    }
}
