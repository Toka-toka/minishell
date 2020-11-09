/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/25 20:47:20 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_point;
	unsigned char	*s2_point;

	s1_point = (unsigned char*)s1;
	s2_point = (unsigned char*)s2;
	while (n > 0)
	{
		if (*s1_point != *s2_point)
			return (*s1_point - *s2_point);
		s1_point++;
		s2_point++;
		n--;
	}
	return (0);
}
