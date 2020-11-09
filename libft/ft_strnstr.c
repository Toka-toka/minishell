/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/29 00:25:00 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*l;
	size_t	i;
	size_t	len_l;
	size_t	len_b;

	i = 0;
	b = (char*)big;
	l = (char*)little;
	len_l = ft_strlen(l);
	len_b = ft_strlen(b);
	if (len_l == 0)
		return (b);
	len = len > len_b ? len_b : len;
	if (len >= len_l)
	{
		while (i + len_l <= len)
		{
			if (ft_memcmp(b + i, l, len_l) == 0)
				return (b + i);
			i++;
		}
	}
	return (NULL);
}
