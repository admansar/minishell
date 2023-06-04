/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chared_info_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:32 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:16:34 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_args(char **split, t_input **list, int i, int *m)
{
	int		n;
	char	**last_split;

	no_surounded_anymore(&split[i]);
	if (char_counter(split[i], '\4'))
	{
		last_split = ft_split(split[i], '\4');
		n = 0;
		while (last_split[n])
			(*list)->arg[(*m)++] = ft_strdup(last_split[n++]);
		free_double_array(last_split);
	}
	else
	{
		(*list)->arg[(*m)] = ft_strdup(split[i]);
		(*m)++;
	}
}

void	list_details(char **split, t_input **list, int *i, int *m)
{
	int	one_time;

	one_time = 1;
	while (split[(*i)])
	{
		if (!ft_strncmp(split[(*i)], ">>", 2))
			list_append(split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], "<<", 2))
			list_heardoc(split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], ">", 2))
			list_out(split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], "<", 1))
			list_in(split, list, (*i)++);
		else if (one_time == 1 && ft_strncmp(split[(*i)], "|", 2))
		{
			list_cmd(split, list, (*i), m);
			one_time = 0;
		}
		else if (!ft_strncmp(split[(*i)], "|", 1))
			break ;
		else
			list_args(split, list, (*i), m);
		(*i)++;
	}
}

void	phil_the_list(t_input **list, char **split)
{
	int		m;
	int		count;
	int		i;
	t_input	*tmp;

	m = 0;
	ambiguous_starter_pack(&split);
	count = ft_strcount(split);
	tmp = *list;
	i = 0;
	while (split[i])
	{
		list_details(split, list, &i, &m);
		if (i >= count)
			break ;
		if (!ft_strcmp(split[i], "|"))
		{
			(*list)->pipe = 1;
			append(*list, count);
			(*list) = (*list)->next;
			m = 0;
		}
		i++;
	}
	(*list) = tmp;
}

void	check_ambiguous(t_input **list)
{
	int	k;
	int	count;
	int	j;

	k = 0;
	while ((*list)->arg[k])
	{
		count = char_counter((*list)->arg[k], '\2');
		if ((count == 1 && ft_strlen((*list)->arg[k]) <= 1) || (count == 1
				&& (*list)->arg[k][0] == '\1' && (*list)->arg[k][1] == '\2'
				&& ft_strlen((*list)->arg[k]) == 2))
		{
			j = k;
			while ((*list)->arg[j + 1])
			{
				free((*list)->arg[j]);
				(*list)->arg[j] = ft_strdup((*list)->arg[j + 1]);
				j++;
			}
			free((*list)->arg[j]);
			(*list)->arg[j] = NULL;
			k = -1;
		}
		k++;
	}
}

void	disable_some_checks(t_input **list)
{
	int	k;

	k = 0;
	while ((*list)->arg[k])
	{
		if (char_counter((*list)->arg[k], '\2'))
			disable(&(*list)->arg[k], '\2');
		if (char_counter((*list)->arg[k], '\1'))
		{
			if ((*list)->arg[k][0] == '\1')
				disable(&(*list)->arg[k], '\1');
			else if ((*list)->arg[k][ft_strlen((*list)->arg[k]) - 1] == '\1')
				disable(&(*list)->arg[k], '\1');
			else
				exchange(&(*list)->arg[k], '\1', ' ');
		}
		k++;
	}
}
