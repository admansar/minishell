/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 09:49:57 by admansar          #+#    #+#             */
/*   Updated: 2023/06/03 09:52:13 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_triple_array(char ***c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free_double_array(c[i]);
		i++;
	}
	free(c);
}

char	**the_repeated(char **tmp1, char **tmp2, char *str, int count)
{
	int		k;
	int		n;
	int		m;
	char	**true_re;
	char	**re;

	m = 0;
	k = -1;
	if (!tmp2)
		return (fill(tmp1));
	re = ft_calloc(sizeof(char *), ((count * ft_strlen(str)) + 1));
	while (tmp1[++k])
	{
		n = -1;
		while (tmp2[++n])
		{
			if (!ft_strcmp(tmp1[k], tmp2[n]))
			{
				re[m++] = ft_strdup(tmp1[k]);
			}
		}
	}
	true_re = fill(re);
	free_double_array(re);
	return (true_re);
}

char	***all_the_reapeated(char **holder, char *str, int h)
{
	int		i;
	int		m;
	char	***all;
	char	**tmp1;
	char	**tmp2;

	i = 0;
	m = 0;
	all = ft_calloc(sizeof(char **), h + 1);
	while (holder[i + 1])
	{
		tmp1 = ft_split(holder[i], '\6');
		tmp2 = ft_split(holder[i + 1], '\6');
		all[m++] = the_repeated(tmp1, tmp2, str, h);
		free_double_array(tmp1);
		free_double_array(tmp2);
		i++;
	}
	return (all);
}

char	**collect_repeated(char *str, char **holder, char **split, int h)
{
	char	***all;
	char	**re;
	int		i;

	all = all_the_reapeated(holder, str, h);
	re = the_repeated(all[0], all[1], str, h);
	free_double_array(split);
	i = 0;
	while (all[i])
	{
		split = fill(re);
		free_double_array(re);
		re = the_repeated(split, all[i], str, h);
		free_double_array(split);
		i++;
	}
	free_triple_array(all);
	free_double_array(holder);
	return (re);
}

char	**get_the_needed_array(char **holder, char **split, char *str)
{
	int		i;
	int		h;
	char	**tmp1;

	i = 0;
	h = (ft_strlen(str) + ft_strcount(split));
	if (holder[i + 1])
		return (collect_repeated(str, holder, split, h));
	else if (holder[i])
	{
		tmp1 = ft_split(holder[i], '\6');
		free_double_array(holder);
		free_double_array(split);
		return (tmp1);
	}
	free_double_array(split);
	return (holder);
}
