/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:00:59 by admansar          #+#    #+#             */
/*   Updated: 2022/10/20 18:19:29 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sc(int n, int fd)
{
	char	a;

	a = '0' + n % 10;
	write(fd, &a, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putnbr_fd(nb / 10, fd);
		write(fd, "8", 1);
	}
	else if (nb == 2147483647)
	{
		ft_putnbr_fd(nb / 10, fd);
		write(fd, "7", 1);
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nb, fd);
	}
	else
	{
		if (nb > 9)
		{
			ft_putnbr_fd(nb / 10, fd);
		}
		sc(nb, fd);
	}
}
