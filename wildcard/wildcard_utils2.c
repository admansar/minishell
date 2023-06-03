/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 09:55:57 by admansar          #+#    #+#             */
/*   Updated: 2023/06/03 09:56:00 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check if s1 is hidden in s2
int	hidden(char *s1, char *s2)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = ft_strlen(s1);
	while (s2[i])
	{
		if (s1[j] == s2[i])
		{
			j++;
			if (j == h)
				break ;
		}
		i++;
	}
	free(s1);
	if (j == h)
		return (1);
	return (0);
}

void	check_for_hidden(char *str, char ***re)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(*re))
		return ;
	tmp = ft_calloc(sizeof(char *), ft_strcount(*re) + 1);
	while ((*re)[i])
	{
		if (hidden(clean_from(str, '*'), (*re)[i]))
		{
			tmp[j] = ft_strdup((*re)[i]);
			j++;
		}
		i++;
	}
	free_double_array(*re);
	*re = fill(tmp);
	free_double_array(tmp);
}

int	re_full_(char ***div, char ***re, int *j)
{
	int	m;

	m = 0;
	while ((*div)[m])
	{
		(*re)[(*j)] = ft_strdup((*div)[m]);
		(*j)++;
		m++;
	}
	(*j)--;
	return (m);
}
