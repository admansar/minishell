/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:39:40 by admansar          #+#    #+#             */
/*   Updated: 2022/10/28 00:02:57 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *fprint, ...);
void	ft_putchar(char c, int *i);
void	ft_putstr(char *c, int *i);
void	ft_putnbr(int n, int *i);
void	ft_putnbr_ui(unsigned int n, int *i);
void	ft_putnbr_hexa(unsigned int nb, int *i);
void	ft_putadres(unsigned long n, int *i);
void	ft_putnbr_hexa_up(unsigned int nb, int *i);
#endif
