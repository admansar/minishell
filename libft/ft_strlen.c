/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:04:14 by admansar          #+#    #+#             */
/*   Updated: 2023/05/01 18:13:57 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(char **c)
{
	int	i;

	i = 0;
	if (!c)
		return (i);
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
