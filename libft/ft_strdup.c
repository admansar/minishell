/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:46:04 by admansar          #+#    #+#             */
/*   Updated: 2022/12/26 17:40:05 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		n;

	i = ft_strlen((char *)s1);
	n = 0;
	ptr = (char *)malloc(sizeof(char) * i + 1);
	if (!ptr)
		return (0);
	while (s1[n])
	{
		ptr[n] = s1[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}
