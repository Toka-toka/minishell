/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: white <white@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:04:05 by white             #+#    #+#             */
/*   Updated: 2021/01/04 21:07:03 by white            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_arg(char **arg)
{
	int		i;

	i = 0;
	if (arg != NULL)
	{
		while (arg[i] != NULL)
		{
			free(arg[i]);
			i++;
		}
	}
	free(arg);
}
