/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:10:16 by admansar          #+#    #+#             */
/*   Updated: 2022/10/27 18:50:39 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned int nb, int *i)
{
	char	*a;

	a = "0123456789abcdef";
	if (nb < 16)
		ft_putchar(a[nb], i);
	else
	{
		ft_putnbr_hexa(nb / 16, i);
		ft_putnbr_hexa(nb % 16, i);
	}
}
