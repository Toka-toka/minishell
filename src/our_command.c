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

void    ft_pwd(t_all *all, char **arg)
{
    char *path;

    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
    free(path);
    all->status = 1;
}

void    ft_cd(t_all *all, char **arg)
{
    char **str;

    if (chdir(arg[1]) == 0)      //В максимально простом варианте это выглядит так
    {
        str = (char **)malloc(sizeof(char *) * 3);
        str[0] = "export";
        str[1] = ft_strjoin("PWD=", arg[1]);
        str[2] = NULL;
        ft_export(all, str);
        free(str);
        all->status = 0;
    }
    else
        all->status = 1; // разные ошибки: если больше одного аргумента или нет такой папки, cd без аргументов перемещает в ~
    
}

void    ft_echo(t_all *all, char **arg)
{
    int i;
    
    i = 1;
    while (arg[i] != NULL)
    {
        if (arg[i][0] == '$' && arg[i][1] == '?')
        {
            ft_putnbr_fd((int)all->status, 1);
        }
        else
            ft_putstr_fd(arg[i], 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
    all->status = 0;
}

void    ft_exit(t_all *all, char **arg)
{  
    all->status = 111;
    printf("all->status (exit)= %d\n", all->status);
    if (arg[1] == NULL)
        exit(0);
    if (arg[2] != NULL)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit(1);
    }
    exit(ft_atoi(arg[1]));
}