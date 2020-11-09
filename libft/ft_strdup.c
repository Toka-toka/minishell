/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/17 17:13:30 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*temp;
	size_t	i;

	temp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (temp != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			temp[i] = s[i];
			i++;
		}
		temp[i] = '\0';
		return (temp);
	}
	return (NULL);
}
