/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:11:43 by admansar          #+#    #+#             */
/*   Updated: 2022/10/17 20:27:27 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	n;

	if (!s || !f)
		return ;
	i = 0;
	n = ft_strlen(s);
	while (i < n)
	{
		f(i, s);
		s++;
		i++;
	}
}
