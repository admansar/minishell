/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:21:33 by admansar          #+#    #+#             */
/*   Updated: 2022/10/26 19:08:55 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *i)
{
	char	a;

	if (nb == -2147483648)
	{
		ft_putnbr(nb / 10, i);
		ft_putchar('8', i);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10, i);
		ft_putnbr(nb % 10, i);
	}
	else if (nb < 0)
	{
		nb = (-1) * nb;
		ft_putchar('-', i);
		ft_putnbr(nb, i);
	}
	else
	{
		a = '0' + (nb % 10);
		ft_putchar(a, i);
	}
}
