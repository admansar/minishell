/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:04:14 by admansar          #+#    #+#             */
/*   Updated: 2023/04/23 15:29:10 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

unsigned long	ft_strlen(char *b)
{
	int	j;

	j = 0;
	if (!b)
		return (j);
	while (b[j])
		j++;
	return (j);
}
