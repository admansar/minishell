/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:05:59 by admansar          #+#    #+#             */
/*   Updated: 2023/06/01 15:10:25 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_dual(const char *s1, const char *s2, size_t n)
{
	int	len1;
	int	len2;

	if ((!s1 && !s2) || !n)
		return (0);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!len1 || !len2)
		return (0);
	while (len1-- && len2-- && n--)
	{
		if (((unsigned char *)s1)[len1] > ((unsigned char *)s2)[len2])
			return (1);
		if (((unsigned char *)s1)[len1] < ((unsigned char *)s2)[len2])
			return (-1);
		if (len1 == 0 || len2 == 0 || n == 0)
			return (0);
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((!s1 && !s2) || !n)
		return (0);
	while (i < n)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
