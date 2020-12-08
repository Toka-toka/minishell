#include "../../includes/minishell.h"

t_envp		*create_var(char *str)
{
	int		i;
	t_envp	*new;

	i = 0;
	new = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		new = (t_envp *)malloc(sizeof(t_envp));
		new->name = ft_substr(str, 0, i);
		new->value = ft_strdup(str + i + 1);
		new->next = NULL;
	}
	return (new);
}

void		add_var(t_all *all, const char *str, int i)
{
	t_envp	*current;
	t_envp	*new;

	new = create_var(str);
	if (new != NULL)
	{
		if (all->envp == NULL)
			all->envp = new;
		else
		{
			current = all->envp;
			while (current->next != NULL &&
			ft_strcmp(new->name, current->name) != 0)
				current = current->next;
			if (ft_strcmp(new->name, current->name) == 0)
			{
				free(current->value);
				current->value = new->value;
				free(new->name);
				free(new);
			}
			else
				current->next = new;
		}
	}
}

void		print_sort_envp(t_all *all, t_envp *current, int len_max)
{
	t_envp	*max;
	int		symb_max;
	int		symb_delt;

	symb_max = -1;
	max = current;
	while (current != NULL)
	{
		if (current->prinf_flag != 1)
		{
			symb_delt = ft_strncmp(max->name, current->name, len_max);
			if (symb_max < symb_delt)
			{
				max = current;
				symb_max = 0;
			}
		}
		current = current->next;
	}
	max->prinf_flag = 1;
	ft_putstr("declare -x ");
	ft_putstr(max->name);
	ft_putstr("=\"");
	ft_putstr(max->value);
	ft_putstr("\"\n");
}

void		sort_envp(t_all *all)
{
	t_envp	*temp;
	int		len_max;

	len_max = 0;
	temp = all->envp;
	while (temp != NULL)
	{
		if (temp->name != NULL && len_max < ft_strlen(temp->name))
			len_max = ft_strlen(temp->name);
		temp->prinf_flag = 0;
		temp = temp->next;
	}
	temp = all->envp;
	while (temp != NULL)
	{
		if (temp->prinf_flag == 1)
			temp = temp->next;
		else
			print_sort_envp(all, temp, len_max);
	}
}

void		ft_export(t_all *all, char **arg)
{
	int		i;

	if (arg[1] == NULL)
		sort_envp(all);
	else
	{
		i = 1;
		while (arg[i] != NULL)
		{
			all->status = 0;
			if ((all->status = var_name_check(arg[i], 1)) == 1)
				print_err("export", arg[1], "not a valid identifier");
			else
				add_var(all, arg[i], 0);
			i++;
		}
	}
}
