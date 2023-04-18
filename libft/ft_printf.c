/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:30:13 by admansar          #+#    #+#             */
/*   Updated: 2022/10/28 18:05:44 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cheker(char ok, va_list ada, int *count, int *i)
{
	if (ok == 'c')
		ft_putchar(va_arg(ada, int), count);
	else if (ok == 's')
		ft_putstr(va_arg(ada, char *), count);
	else if (ok == 'p')
	{
		ft_putstr("0x", count);
		ft_putadres(va_arg(ada, unsigned long), count);
	}
	else if (ok == 'i' || ok == 'd')
		ft_putnbr(va_arg(ada, int), count);
	else if (ok == 'u')
		ft_putnbr_ui(va_arg(ada, unsigned int), count);
	else if (ok == 'x')
		ft_putnbr_hexa(va_arg(ada, unsigned int), count);
	else if (ok == 'X')
		ft_putnbr_hexa_up(va_arg(ada, unsigned int), count);
	else if (ok == '%')
		ft_putchar('%', count);
	(*i)++;
}

int	ft_printf(const char *ok, ...)
{
	int		i;
	int		count;
	va_list	ada;

	i = 0;
	count = 0;
	va_start(ada, ok);
	while (ok[i])
	{
		if (ok[i] == '%')
		{
			i++;
			cheker(ok[i], ada, &count, &i);
		}
		else
		{
			ft_putchar(ok[i], &count);
			i++;
		}
	}
	return (count);
}
