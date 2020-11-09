/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/25 20:46:24 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int symbol, size_t n)
{
	unsigned char	*dest_point;
	unsigned char	*src_point;
	unsigned char	ch_symbol;
	size_t			i;

	i = 0;
	ch_symbol = symbol;
	dest_point = (unsigned char*)dest;
	src_point = (unsigned char*)src;
	if (dest_point == NULL && src_point == NULL)
		return (NULL);
	while (i < n)
	{
		dest_point[i] = src_point[i];
		if (src_point[i] == ch_symbol)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
