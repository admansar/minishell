/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_most_nedded_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 09:54:04 by admansar          #+#    #+#             */
/*   Updated: 2023/06/03 18:05:37 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	the_start_of_the_beg_dual(char *copy, char **ls, int j, char ***holder)
{
	int	i;
	int	h;
	int	pass;
	int	k;

	i = 0;
	h = ft_strlen(copy);
	pass = 1;
	k = 0;
	while (ls[k])
	{
		if (!ft_strncmp_dual(copy, ls[k], h) && pass == 1)
		{
			(*holder)[j] = ft_strdup(ls[k]);
			(*holder)[j] = ft_str_join((*holder)[j], "\6");
			pass = 0;
		}
		else if (!ft_strncmp_dual(copy, ls[k], h))
		{
			(*holder)[j] = ft_str_join((*holder)[j], "\6");
			(*holder)[j] = ft_str_join((*holder)[j], ls[k]);
		}
		k++;
	}
	free(copy);
}

void	the_start_of_the_beg(char *copy, char **ls, char ***holder)
{
	int	i;
	int	h;
	int	pass;
	int	k;

	i = 0;
	h = ft_strlen(copy);
	pass = 1;
	k = 0;
	while (ls[k])
	{
		if (!ft_strncmp(copy, ls[k], h) && pass == 1)
		{
			(*holder)[0] = ft_strdup(ls[k]);
			(*holder)[0] = ft_str_join((*holder)[0], "\6");
			pass = 0;
		}
		else if (!ft_strncmp(copy, ls[k], h))
		{
			(*holder)[0] = ft_str_join((*holder)[0], "\6");
			(*holder)[0] = ft_str_join((*holder)[0], ls[k]);
		}
		k++;
	}
	free(copy);
}

void	find_and_collect_no_p(char **ls, char ***holder, int *j, char *split)
{
	int	pass;
	int	k;
	int	h;

	pass = 1;
	k = 0;
	while (ls[k])
	{
		h = ft_strlen(ls[k]);
		if (ft_strnstr(ls[k], split, h) && pass == 1 && ls[k][0] != '.')
		{
			(*holder)[*j] = ft_strdup(ls[k]);
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			pass = 0;
		}
		else if (ft_strnstr(ls[k], split, h) && ls[k][0] != '.')
		{
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			(*holder)[*j] = ft_str_join((*holder)[*j], ls[k]);
		}
		k++;
	}
	if ((*holder)[*j])
		(*j)++;
}

void	find_and_collect(char **ls, char ***holder, int *j, char *split)
{
	int	pass;
	int	k;
	int	h;

	pass = 1;
	k = 0;
	while (ls[k])
	{
		h = ft_strlen(ls[k]);
		if (ft_strnstr(ls[k], split, h) && pass == 1)
		{
			(*holder)[*j] = ft_strdup(ls[k]);
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			pass = 0;
		}
		else if (ft_strnstr(ls[k], split, h))
		{
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			(*holder)[*j] = ft_str_join((*holder)[*j], ls[k]);
		}
		k++;
	}
	if ((*holder)[*j])
		(*j)++;
}

char	**the_commun(char **str, char **ls)
{
	char	**tmp;
	char	**re;
	int		i;
	int		j;

	no_extra_(&(*str), '*');
	tmp = malloc(sizeof(char *) * (ft_strcount(ls) + 1));
	i = 0;
	j = 0;
	while (ls[i])
	{
		if (ls[i][0] != '.')
			tmp[j++] = ft_strdup(ls[i]);
		i++;
	}
	tmp[j] = NULL;
	re = fill(tmp);
	free_double_array(tmp);
	return (re);
}
