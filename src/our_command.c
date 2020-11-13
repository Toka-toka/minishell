#include "../includes/minishell.h"

int     var_name_check(char *name, int j) // j = 0 для unset и j = 1 для export
{
    int i;
    int flag;

    i = 0;
    flag = 1;
    while (name[i] != '\0')
    {
        if (j == 0 && name[i] == '=')
        {
            flag = 1;
            break;
        }
        if (name[i] < '0' || name[i] > '9')
            flag = 0;
        i++;
    }
    return(flag);
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
            add_var(all, arg[i]);
            i++;
        }
    }
}

void    ft_unset(t_all *all, char **arg)
{
    int i;
    
    i = 0;
    while (arg[i] != NULL)
    {
        printf("arg = %s\n", arg[i]);
        i++;
    }
    i = 1;
    if (arg != NULL && arg[0] != NULL && arg[1] != NULL)
    {
        while (arg[i] != NULL)
        {
            if (var_name_check(arg[i], 0) == 1)
            {
                ft_putstr("unset: "); // куда нужно направлять ошибки...?
                ft_putstr(arg[i]);
                ft_putstr(": not a valid identifier\n");  
            }
            del_var(all, arg[i]);
            i++;
        }
    }
}

void    ft_env(t_all *all, char **arg)
{
    int i = 0;
    
    while (arg[i] != NULL)
    {
        printf("arg = %s\n", arg[i]);
        i++;
    }

//    if (arg[1] != NULL)
//        ft_putstr("env: works only without arguments");
    print_envp(all, 0);
}
// env

//pwd