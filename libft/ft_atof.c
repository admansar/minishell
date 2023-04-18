/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:41:16 by admansar          #+#    #+#             */
/*   Updated: 2023/01/31 14:51:49 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	_continue(int i, const char *str)
{
	double	c;
	double	sa;

	if (str[i] == '.')
		i++;
	else
		return (0);
	c = 1;
	sa = 0;
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		c = c / 10;
		sa = sa + c * (str[i] - 48);
		i++;
	}
	return (sa);
}

double	ft_atof(const char *str)
{
	int		i;
	int		count;
	double	sa;
	int		d;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	d = 0;
	count = 1;
	if (str[i] == '-')
	{
		count = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		d = d * 10;
		d = d + str[i] - 48;
		i++;
	}
	sa = _continue(i, str);
	return (count * (d + sa));
}
