/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:31:06 by admansar          #+#    #+#             */
/*   Updated: 2022/12/26 17:38:16 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (dst == 0 && size == 0)
		return ((size_t)ft_strlen((char *)src));
	j = 0;
	i = ft_strlen(dst);
	if (size <= i || size == 0)
		return (size + (size_t)ft_strlen((char *)src));
	while (src[j] && j < size - i - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + (size_t)ft_strlen((char *)src));
}
