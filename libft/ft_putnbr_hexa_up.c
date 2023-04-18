/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:53:44 by admansar          #+#    #+#             */
/*   Updated: 2022/10/27 23:57:26 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa_up(unsigned int nb, int *i)
{
	char	*a;

	a = "0123456789ABCDEF";
	if (nb < 16)
		ft_putchar(a[nb], i);
	else
	{
		ft_putnbr_hexa_up(nb / 16, i);
		ft_putnbr_hexa_up(nb % 16, i);
	}
}
