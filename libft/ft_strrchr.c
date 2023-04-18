/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:56:16 by admansar          #+#    #+#             */
/*   Updated: 2022/12/26 17:39:15 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	r;

	r = ft_strlen((char *)s);
	i = r;
	while (i >= 0)
	{
		if (((char *)s)[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
