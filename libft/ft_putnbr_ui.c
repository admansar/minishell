/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:58:39 by admansar          #+#    #+#             */
/*   Updated: 2022/10/27 17:03:54 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_ui(unsigned int nb, int *i)
{
	char	a;

	if (nb > 9)
	{
		ft_putnbr_ui(nb / 10, i);
		ft_putnbr_ui(nb % 10, i);
	}
	else
	{
		a = '0' + (nb % 10);
		ft_putchar(a, i);
	}
}
