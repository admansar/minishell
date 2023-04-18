/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:17:24 by admansar          #+#    #+#             */
/*   Updated: 2023/04/13 17:55:28 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*g_g(char *ptr, const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		ptr[i + n] = s2[n];
		n++;
	}
	ptr[i + n] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	ptr = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!ptr)
		return (NULL);
	g_g(ptr, s1, s2);
	return (ptr);
}
