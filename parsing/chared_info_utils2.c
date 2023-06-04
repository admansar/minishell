/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chared_info_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:54 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:43:01 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_append(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable(&split[i], '\2');
	if (char_counter(split[i + 1], '\2'))
		disable(&split[i + 1], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "2";
	if (split[i + 1])
		(*list)->redirect->file_name[(*list)->redirect->position]
			= ft_strdup(split[++i]);
	(*list)->redirect->position++;
}

void	list_heardoc(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable(&split[i], '\2');
	if (char_counter(split[i + 1], '\2'))
		disable(&split[i + 1], '\2');
	(*list)->redirect->type[(*list)->redirect->position] = "4";
	if (split[i + 1])
		(*list)->redirect->file_name[(*list)->redirect->position]
			= ft_strdup(split[++i]);
	(*list)->redirect->position++;
}

void	list_in(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable(&split[i], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "3";
	if (split[i + 1])
		(*list)->redirect->file_name[(*list)->redirect->position]
			= ft_strdup(split[++i]);
	(*list)->redirect->position++;
}

void	list_out(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable(&split[i], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "1";
	if (split[i + 1])
		(*list)->redirect->file_name[(*list)->redirect->position]
			= ft_strdup(split[++i]);
	(*list)->redirect->position++;
}

void	list_cmd(char **split, t_input **list, int i, int *m)
{
	int		n;
	char	**last_split;

	if (char_counter(split[i], '\2'))
		disable(&split[i], '\2');
	if (char_counter(split[i], '\1'))
		exchange(&split[i], '\1', ' ');
	no_surounded_anymore(&split[i]);
	if (char_counter(split[i], '\4'))
	{
		last_split = ft_split(split[i], '\4');
		n = 0;
		(*list)->cmd = ft_strdup(last_split[n++]);
		while (last_split[n])
			(*list)->arg[(*m)++] = ft_strdup(last_split[n++]);
		free_double_array(last_split);
	}
	else
		(*list)->cmd = ft_strdup(split[i]);
}
