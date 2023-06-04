/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chared_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:17:34 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:17:35 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	phil_list(t_input **list, char **split)
{
	t_input	*tmp;

	phil_the_list(list, split);
	tmp = *list;
	while (*list)
	{
		check_ambiguous(list);
		disable_some_checks(list);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

int	ft_strmegacount(char **c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			j++;
		}
		count += j;
		i++;
	}
	return (count);
}

t_input	*work_time(char **split)
{
	t_input	*list;

	init_list(&list, ft_strmegacount(split));
	phil_list(&list, split);
	return (list);
}

void	free_list(t_input *list)
{
	t_input	*tmp;

	tmp = list;
	while (tmp)
	{
		free(tmp->cmd);
		free_double_array(tmp->arg);
		free(tmp->redirect->type);
		free_double_array(tmp->redirect->file_name);
		free(tmp->redirect);
		list = list->next;
		free(tmp);
		tmp = list;
	}
}

int	check_error(char **str, int i)
{
	int	h;

	h = ft_strlen(str[i]);
	if (str[i + 1][0] == '|' && str[i][h - 1] == '>')
		return (i);
	if (str[i + 1][0] == '|' && str[i][h - 1] == '<')
		return (i);
	if (str[i + 1][0] == '>' && str[i][h - 1] == '<')
		return (i);
	if (str[i + 1][0] == '<' && str[i][h - 1] == '>')
		return (i);
	return (-1);
}
