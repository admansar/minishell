/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:17:24 by admansar          #+#    #+#             */
/*   Updated: 2023/04/24 00:41:31 by admansar         ###   ########.fr       */
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

char	*ft_str_join(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1) + 1;
	s2len = ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!ptr)
		return (NULL);
	g_g(ptr, s1, s2);
	free(s1);
	return (ptr);
}
