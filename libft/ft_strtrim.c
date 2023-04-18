/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:39:38 by admansar          #+#    #+#             */
/*   Updated: 2022/12/26 17:44:59 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	i;
	size_t	l;
	size_t	n;

	if (!set || !s1)
		return (NULL);
	n = 0;
	while (ft_strchr(set, s1[n]) && s1[n])
		n++;
	l = ft_strlen((char *)s1);
	while (n < l && ft_strchr(set, s1[l - 1]) && l > 0)
		l--;
	p = (char *)malloc((l - n) + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (n < l)
	{
		p[i++] = s1[n++];
	}
	p[i] = '\0';
	return (p);
}
