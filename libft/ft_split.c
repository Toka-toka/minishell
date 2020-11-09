/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:13:04 by sedric            #+#    #+#             */
/*   Updated: 2020/05/25 20:42:13 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_cubalibre(int *app, char **split, int i)
{
	free(app);
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static int		*ft_wordsearch(char const *s, int *arr, char c)
{
	arr[0] = arr[0] + arr[1];
	arr[1] = 0;
	while (s[arr[0]] == c)
		arr[0]++;
	while (s[arr[0] + arr[1]] != c && s[arr[0] + arr[1]] != '\0')
		arr[1]++;
	return (arr);
}

static char		**ft_mallocmaster(int words, char const *s, char c)
{
	char		**split;
	int			i;
	int			*arr;

	split = (char**)malloc((words + 1) * sizeof(char *));
	arr = ft_calloc(sizeof(int), 2);
	if (split == NULL || arr == NULL)
	{
		free(split);
		return (NULL);
	}
	i = 0;
	while (i < words)
	{
		ft_wordsearch(s, arr, c);
		split[i] = ft_substr(s, (unsigned int)arr[0], (size_t)arr[1]);
		if (split[i] == NULL)
			return (ft_cubalibre(arr, split, i));
		i++;
	}
	free(arr);
	split[i] = NULL;
	return (split);
}

char			**ft_split(char const *s, char c)
{
	char		**split;
	int			words;
	int			i;

	if (s == NULL)
		return (NULL);
	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	split = ft_mallocmaster(words, s, c);
	return (split);
}
