/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:17:41 by admansar          #+#    #+#             */
/*   Updated: 2022/10/10 04:54:28 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t l)
{
	size_t	i;
	size_t	j;
	size_t	a;

	i = 0;
	if (n[i] == 0)
		return ((char *)h);
	if (l == 0)
		return (NULL);
	while (h[i] && i < l)
	{
		j = 0;
		a = i;
		while (h[a] == n[j] && a < l)
		{
			if (n[j + 1] == '\0')
				return ((char *)h + i);
			j++;
			a++;
		}
		i++;
	}
	return (0);
}
