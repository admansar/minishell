/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_join_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:07:54 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:07:58 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_last_spaces(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
		check_delete(&(*str)[i++]);
}

// no comment
void	no_etxra_qoutes(char ***str)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	while ((*str)[i])
	{
		s = ft_simularity_len((*str)[i], '\'');
		d = ft_simularity_len((*str)[i], '\"');
		if (s < d && char_counter((*str)[i], '\'') >= 2)
			delete_them_inside(&(*str)[i], '\'');
		else if (d < s && char_counter((*str)[i], '\"') >= 2)
			delete_them_inside(&(*str)[i], '\"');
		i++;
	}
	delete_last_spaces(str);
}

void	space_append_heardoc(char **tmp, int *i, int *j, int type)
{
	if (type == 2)
	{
		(*tmp)[(*j)++] = ' ';
		(*tmp)[(*j)++] = '>';
		(*tmp)[(*j)++] = '>';
		(*tmp)[(*j)++] = ' ';
		(*i) += 2;
	}
	else if (type == 4)
	{
		(*tmp)[(*j)++] = ' ';
		(*tmp)[(*j)++] = '<';
		(*tmp)[(*j)++] = '<';
		(*tmp)[(*j)++] = ' ';
		(*i) += 2;
	}
}

void	space_char(char **tmp, int *i, int *j, char c)
{
	(*tmp)[(*j)++] = ' ';
	(*tmp)[(*j)++] = c;
	(*tmp)[(*j)++] = ' ';
	(*i)++;
}
