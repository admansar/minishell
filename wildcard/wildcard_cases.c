/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 09:40:09 by admansar          #+#    #+#             */
/*   Updated: 2023/06/03 09:47:50 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**the_end(char *str, char **ls)
{
	int		i;
	int		j;
	char	*copy;
	char	**split;
	char	**holder;

	i = ft_strlen(str);
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
					'*') + 5));
	copy = take_copy(str, ft_simularity_len_dual(str, '*') + 1, ft_strlen(str)
			- 1);
	the_start_of_the_beg_dual(copy, ls, j, &holder);
	if (holder[j])
		j++;
	i = 0;
	while (split[i + 1])
		find_and_collect_no_p(ls, &holder, &j, split[i++]);
	return (get_the_needed_array(holder, split, str));
}

char	**the_inner(char *str, char **ls)
{
	char	**split;
	char	**holder;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
					'*') + ft_strcount(ls) + 1));
	while (split[i])
	{
		find_and_collect_no_p(ls, &holder, &j, split[i]);
		i++;
		if (holder[j])
			j++;
	}
	return (get_the_needed_array(holder, split, str));
}

char	**the_popular_choice(char *str, char **ls)
{
	char	*copy;
	int		i;
	int		j;
	char	**split;
	char	**holder;

	i = 0;
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
					'*') + 5));
	copy = take_copy(str, 0, ft_simularity_len(str, '*') - 1);
	the_start_of_the_beg(copy, ls, &holder);
	if (holder[j])
		j++;
	copy = take_copy(str, ft_simularity_len_dual(str, '*') + 1, ft_strlen(str)
			- 1);
	the_start_of_the_beg_dual(copy, ls, j, &holder);
	if (holder[j])
		j++;
	i = 1;
	while (split[++i])
		find_and_collect(ls, &holder, &j, split[i]);
	return (get_the_needed_array(holder, split, str));
}

char	**the_beg(char *str, char **ls)
{
	char	*copy;
	int		i;
	int		j;
	char	**split;
	char	**holder;

	i = 0;
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
					'*') + 5));
	while (str[i] && str[i] != '*')
		i++;
	copy = take_copy(str, 0, i - 1);
	the_start_of_the_beg(copy, ls, &holder);
	if (holder[j])
		j++;
	i = 1;
	while (split[i])
	{
		find_and_collect(ls, &holder, &j, split[i]);
		i++;
	}
	return (get_the_needed_array(holder, split, str));
}
