#include "../includes/minishell.h"

// добавление элемента (если есть то просмотр аргументов)

void    add_var(t_all *all, const char *str) // поиск по имени?
{
    t_envp *current;
    t_envp *new;
    int     i;
    
    i = 0;
    while (str[i] != '=' && str[i] != '\0')
        i++;
    if (str[i] == '=')
    {
        new = (t_envp *)malloc(sizeof(t_envp));
        new->name = ft_substr(str, 0, i);
        new->value = ft_strdup(str + i + 1);
        new->next = NULL;
        if (all->envp->value == NULL) //что будет если удалить все и начать записывать заново
            all->envp = new;
        else
        {
            current = all->envp;
            while (current->next != NULL && ft_memcmp(str, current->name, i) != 0)
                current = current->next;
            if (ft_memcmp(str, current->name, i) == 0)
            {
                free(current->value);
                current->value = new->value;
                free(new);
                free(new->name);
            }
            else
                current->next = new;
        }
    }
}

// удаление элемента (если параметр NULL то удаление всего списка)

void    del_var(t_all *all, char *name)
{
    t_envp  *current;
    t_envp  *prev;
    int     len;

    len = ft_strlen(name);
    current = all->envp;
    while (current != NULL)
    {
        if (ft_memcmp(name, current->name, len) == 0)
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

void    print_envp(t_all *all, int i) // печать всего списка (с приставкой и без)
{
    t_envp  *temp;

    temp = all->envp;
    while (temp != NULL)
    {
        if (i == 1)
            ft_putstr("declare -x ");
        ft_putstr(temp->name);
        ft_putstr("=");
        ft_putstr(temp->value);
        ft_putstr("\n");
        temp = temp->next;
    }
}

char    **arr_from_list(t_all *all) // создание массива из списка
{
    t_envp  *current;
    char    **arr;
    char    *temp;
    int     i;

    printf("all = %p\n", all);
    i = 0;
    current = all->envp;
    while (current != NULL)
    {
        current = current->next;
        i++;
    }
    arr = (char **)malloc(sizeof(char *) * (i));
    current = all->envp;
    i = 0;
    while (current != NULL)
    {
        temp = ft_strjoin(current->name, "=");
        arr[i] = ft_strjoin(temp, current->value);
        i++;
        current = current->next;
    }
    arr[i] = NULL;
    return(arr);
}

char    *search_var(t_all *all, char *name)
{
    t_envp  *current;
    char    *temp;
    int     len;

    len = ft_strlen(name);
    current = all->envp;
    while (current != NULL)
    {
        if (ft_memcmp(name, current->name, len) == 0)
            return(current->value);
        current = current->next;
    }
    return(NULL);
}