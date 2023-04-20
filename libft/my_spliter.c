/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:02:08 by admansar          #+#    #+#             */
/*   Updated: 2023/04/20 15:34:43 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	space_counter(char *s)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	j++;
	return (j);
}

char	*cutter(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	while (s[i])
	{
		while (s[i] == ' ' && s[i + 1] == ' ')
		{
			i++;
		}
		tmp[j] = s[i];
		j++;
		i++;
	}
	return (tmp);
}

char	*protecter(char *str, int i)
{
	int		j;
	int		k;
	char	*re;

	i = 0;
	while (str[i] == ' ')
		i++;
	j = i;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ')
		i--;
	k = i + 1;
	re = ft_calloc(i + 2, sizeof(char));
	i = j;
	j = 0;
	while (str[i])
	{
		re[j++] = str[i++];
		if (i == k)
			break ;
	}
	free(str);
	return (re);
}

char	**norm(char *s, char **re)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == ' ' && i > 0)
		{
			re[j][k] = s[i];
			k = 0;
			i++;
			j++;
		}
		re[j][k] = s[i];
		i++;
		k++;
	}
	return (re);
}

char	**my_spliter(char *s, int i, int j, int k)
{
	char	**re;

	s = cutter(s);
	s = protecter(s, 0);
	re = ft_calloc(sizeof(char *), (space_counter(s) + 1));
	while (s[i])
	{
		if (s[i] == ' ' && i > 0)
		{
			re[j] = ft_calloc(sizeof(char), (i - k + 2));
			j++;
			k = i;
			k++;
		}
		i++;
	}
	re[j] = ft_calloc(sizeof(char), (i - k + 2));
	re = norm(s, re);
	free(s);
	return (re);
}
