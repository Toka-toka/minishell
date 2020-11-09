/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/20 12:05:27 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	len_begin;
	size_t	len_end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_begin = 0;
	while (ft_strrchr(set, s1[len_begin]) != 0 && s1[len_begin] != '\0')
		len_begin++;
	if (s1[len_begin] != '\0')
	{
		len_end = ft_strlen(s1);
		while (ft_strrchr(set, s1[len_end - 1]) != 0)
			len_end--;
		strtrim = ft_substr(s1, len_begin, (len_end - len_begin));
	}
	else
	{
		if (!(strtrim = malloc(sizeof(char) * 1)))
			return (NULL);
		strtrim[0] = '\0';
	}
	return (strtrim);
}
