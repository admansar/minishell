/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:18:00 by admansar          #+#    #+#             */
/*   Updated: 2022/10/08 13:07:15 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		i;
	char	*c_s1;
	char	*c_s2;

	c_s1 = (char *)s1;
	c_s2 = (char *)s2;
	i = 0;
	while ((size_t)i < n)
	{
		if (c_s1[i] != c_s2[i])
			return ((unsigned char)c_s1[i] - (unsigned char)c_s2[i]);
		i++;
	}
	return (0);
}
