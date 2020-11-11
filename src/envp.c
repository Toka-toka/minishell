#include "../includes/minishell.h"

// добавление элемента (если есть то просмотр аргументов)

void    add_var(t_all *all, const char *str)
{
    char *temp;
    t_envp *current;
    t_envp *new;
    
//  temp = str;
    new = (t_envp *)malloc(sizeof(t_envp));
    new->value = ft_strdup(str);
    new->next = NULL;
    printf("%s\n%s\n", str, new->value);
//    if (all->envp == NULL)
//        all->envp = new;
//    else
//    {
    current = all->envp;
    while (current != NULL)
        current = current->next;
    current = new;
//    }
}

// удаление элемента (если параметр NULL то удаление всего списка)

// печать всего списка (с приставкой и без)

// создание массива из списка