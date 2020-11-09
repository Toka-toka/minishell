/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/25 20:46:52 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *arr, int symbol, size_t n)
{
	unsigned char	*arr_point;
	unsigned char	ch_symbol;
	int				i;
	int				size;

	arr_point = (unsigned char*)arr;
	i = 0;
	size = n - 1;
	ch_symbol = symbol;
	while (i < size && arr_point[i] != ch_symbol)
		i++;
	if (arr_point[i] == ch_symbol && n != 0)
		return (arr_point + i);
	else
		return (NULL);
}
