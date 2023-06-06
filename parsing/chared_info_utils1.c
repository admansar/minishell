/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chared_info_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:03 by admansar          #+#    #+#             */
/*   Updated: 2023/06/06 12:27:13 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_list(t_input **list, int count)
{
	(*list) = malloc(sizeof(t_input));
	(*list)->next = NULL;
	(*list)->cmd = NULL;
	(*list)->arg = ft_calloc(sizeof(char *), count + 1);
	(*list)->redirect = malloc(sizeof(t_redirection));
	(*list)->redirect->file_name = ft_calloc(sizeof(char *), count + 1);
	(*list)->redirect->type = ft_calloc(sizeof(char *), count + 1);
	(*list)->redirect->position = 0;
	ft_bzero((*list)->redirect->herdoc_file_name, 30);
	(*list)->pipe = 0;
}

t_input	*append(t_input *list, int count)
{
	while (list->next)
		list = list->next;
	init_list(&list->next, count);
	return (list);
}

int	mega_counter(char **str, char c)
// returns num of repetitions of a char in a double str
{
	int	i;
	int	re;

	i = 0;
	re = 0;
	while (str[i])
	{
		re += char_counter(str[i], c);
		i++;
	}
	return (re);
}

void	exchange(char **ptr, char c, char b)
{
	int	i;

	i = 0;
	while ((*ptr)[i])
	{
		if ((*ptr)[i] == c)
			(*ptr)[i] = b;
		i++;
	}
}

void	ambiguous_starter_pack(char ***split)
{
	int	i;
	int	count;

	i = 0;
	while ((*split)[i])
	{
		count = char_counter((*split)[i], '\2');
		if ((count == 1 && (*split)[i][0] == '\1' && (*split)[i][1] == '\2'
				&& ft_strlen((*split)[i]) == 2))
			disable(&(*split)[i], '\1');
		if (char_counter((*split)[i], '\5'))
			exchange(&(*split)[i], '\5', ' ');
		i++;
	}
}
