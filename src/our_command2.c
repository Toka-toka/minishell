#include "../includes/minishell.h"

void    ft_pwd(t_all *all, char **arg)
{
    char *path;

    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
    free(path);
    all->status = 1;
}

void    change_pwd(t_all *all, char *oldpwd)
{
    char *pwd_envp;
    char *oldpwd_envp;
    char *temp[3];
    
    pwd_envp = search_var(all, "PWD");
    oldpwd_envp = search_var(all, "OLDPWD");
    temp[0] = "export";
    if (oldpwd_envp != NULL)
    {
        temp[2] = ft_strjoin("OLDPWD", "=");
        if (pwd_envp != NULL)
            temp[1] = ft_strjoin(temp[2], pwd_envp);
        else
            temp[1] = ft_strjoin(temp[2], oldpwd);
        free(temp[2]);
        temp[2] = NULL;
        ft_export(all, temp);
    }
    if (pwd_envp != NULL)
    {
        pwd_envp = getcwd(NULL, 0);
        temp[2] = ft_strjoin("PWD", "=");
        temp[1] = ft_strjoin(temp[2], pwd_envp);
        free(temp[2]);
        temp[2] = NULL;
        ft_export(all, temp);
    }
}

void    print_cd_errors(t_all *all, char *arg)
{
    ft_putstr_fd("cd: ", 2);
    if (errno == 225)
        ft_putstr_fd("Не задана переменная HOME\n", 2);
    else if (errno == 224)
        ft_putstr_fd("too many arguments\n", 2);
    else
    {
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
    }
    all->status = 1;
}

void    ft_cd(t_all *all, char **arg)
{
    char *path;
    int i = 0;
    char *pwd;

    errno = 0;
    pwd = getcwd(NULL, 0);
    if (arg[1] == NULL)
    {
        if ((path = search_var(all, "HOME")) == NULL)
            errno = 225;
    }
    else if (arg[2] != NULL)
        errno = 224;
    else
        path = arg[1];
    if (errno == 0 && chdir(path) == 0)
    {
        change_pwd(all, pwd);
        all->status = 0;
    }
    else
        print_cd_errors(all, path);
    if (pwd != NULL)
        free(pwd);
}
