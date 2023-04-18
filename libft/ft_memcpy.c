/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:36:32 by admansar          #+#    #+#             */
/*   Updated: 2022/10/02 19:39:45 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cast_dst;
	char	*cast_src;
	int		i;

	if (!dst && !src)
		return (NULL);
	cast_dst = (char *)dst;
	cast_src = (char *)src;
	i = 0;
	while (n)
	{
		cast_dst[i] = cast_src[i];
		n--;
		i++;
	}
	return (cast_dst);
}
