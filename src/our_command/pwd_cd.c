
#include "../../includes/minishell.h"

void		call_export(t_all *all, char *name, char *value)
{
	char	*temp[3];

	temp[0] = "export";
	temp[2] = ft_strjoin(name, "=");
	temp[1] = ft_strjoin(temp[2], value);
	free(temp[2]);
	temp[2] = NULL;
	ft_export(all, temp);
	free(temp[1]);
}

void		ft_pwd(t_all *all, char **arg)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		free(path);
	}
	else
	{
		print_err("pwd", NULL, strerror(errno));
		all->status = 1;
	}
}

void		change_pwd(t_all *all, char *oldpwd)
{
	char	*pwd_envp;
	char	*oldpwd_envp;

	pwd_envp = NULL;
	if ((oldpwd_envp = search_var(all, "OLDPWD")) != NULL)
	{
		if ((pwd_envp = search_var(all, "PWD")) != NULL)
			call_export(all, "OLDPWD", pwd_envp);
		else
			call_export(all, "OLDPWD", oldpwd);
	}
	if (pwd_envp != NULL)
	{
		pwd_envp = getcwd(NULL, 0);
		call_export(all, "PWD", pwd_envp);
		free(pwd_envp);
	}
}

void		print_cd_errors(t_all *all, char *arg)
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

void		ft_cd(t_all *all, char **arg)
{
	char	*path;
	char	*pwd;

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
		change_pwd(all, pwd);
	else
		print_cd_errors(all, path);
	if (pwd != NULL)
		free(pwd);
}
