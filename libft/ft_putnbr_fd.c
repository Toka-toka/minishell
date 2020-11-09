/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:00:47 by sedric            #+#    #+#             */
/*   Updated: 2020/05/25 20:14:25 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			temp[11];
	unsigned int	number;
	int				i;

	i = 0;
	number = n >= 0 ? n : -n;
	while (number != 0 || i == 0)
	{
		temp[i] = number % 10 + 48;
		number = number / 10;
		i++;
	}
	if (n < 0)
	{
		temp[i] = '-';
		i++;
	}
	while (i > 0)
	{
		i--;
		write(fd, &temp[i], 1);
	}
}
