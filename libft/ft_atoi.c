/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:12:54 by sedric            #+#    #+#             */
/*   Updated: 2020/05/15 21:58:59 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int				i;
	int				flag;
	unsigned long	number;

	i = 0;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	flag = (*str == 45 ? -1 : 1);
	if (*str == 43 || *str == 45)
		str++;
	while (*str == 48)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		number = *str - 48 + number * 10;
		i++;
		str++;
	}
	if (number > 9223372036854775807 || i >= 20)
		return (-0.5 * (flag + 1));
	return (number * flag);
}
