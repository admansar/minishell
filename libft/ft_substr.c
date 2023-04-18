/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:11:42 by admansar          #+#    #+#             */
/*   Updated: 2022/12/26 17:43:27 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*maker(char *s, char *ptr, size_t start, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (((char *)s)[i])
	{
		if (i >= (size_t)start && n < len)
		{
			ptr[n] = ((char *)s)[i];
			n++;
		}
		i++;
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > (size_t)ft_strlen((char *)s))
	{
		ptr = (char *)malloc(sizeof(char) * ft_strlen((char *)s) + 1);
		maker((char *)s, ptr, start, len);
		return (ptr);
	}
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	maker((char *)s, ptr, start, len);
	return (ptr);
}
