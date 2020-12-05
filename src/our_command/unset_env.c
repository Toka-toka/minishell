#include "../../includes/minishell.h"

char    *search_var(t_all *all, char *name)
{
    t_envp  *current;
    char    *temp;
    int     len;

    len = ft_strlen(name);
    len++;
    current = all->envp;
    while (current != NULL)
    {
        if (ft_memcmp(name, current->name, len) == 0)
            return(current->value);
        current = current->next;
    }
    return(NULL);
}

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

void    del_var(t_all *all, char *name)
{
    t_envp  *current;
    t_envp  *prev;
    int     len;
    char    *temp;

    current = all->envp;
    temp = name;
    while (current != NULL)
    {
        if (name == NULL)
            temp = current->name;
        if (strcmp(temp, current->name) == 0)
        {
            free(current->name);
            free(current->value);
            if (current == all->envp)
                all->envp = current->next;
            else
                prev->next = current->next;
            free(current);
        }
        prev = current;
        current = current->next;
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
            all->status = 0;
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
     t_envp  *temp;
    
    if (arg[1] != NULL)
    {
        ft_putstr("env: works only without arguments\n"); // во второй поток
        all->status = 1;
    }
    else
    {
        temp = all->envp;
        while (temp != NULL)
        {
            ft_putstr(temp->name);
            ft_putstr("=");
            ft_putstr(temp->value);
            ft_putstr("\n");
            temp = temp->next;
        }
    }
}