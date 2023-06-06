/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:57:10 by admansar          #+#    #+#             */
/*   Updated: 2023/06/06 12:49:24 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// better for cheking errors the advantage of it that
// i split the double quote without waisting the double quotes
char	**split_without_weast(char **input)
{
	t_parse	*pars;
	char	**new_str;

	pars = malloc(sizeof(t_parse));
	new_str = malloc(sizeof(char *) * ft_strlen((*input)));
	pars->start = 0;
	pars->end = 0;
	pars->taken = 1;
	pars->j = 0;
	pars->i = 0;
	while ((*input)[pars->i])
		split_without_weast_utils(pars, &new_str, input);
	new_str[pars->j] = NULL;
	if (pars->start > pars->end)
	{
		free_double_array(new_str);
		new_str = NULL;
		free (pars);
		return (NULL);
	}
	free(pars);
	return (new_str);
}

void	search_and_replace(t_parse *pars, char **input)
{
	if ((*input)[pars->i] == '\'' && pars->taken == 1)
	{
		pars->start = pars->i;
		pars->taken = 0;
	}
	else if ((*input)[pars->i] == '\'' && pars->taken == 0)
	{
		pars->end = pars->i;
		pars->taken = 1;
	}
	if (pars->start < pars->end)
	{
		pars->str = take_copy((*input), pars->start, pars->end);
		if (!char_counter(pars->str, '\"') && !char_counter(pars->str, '$'))
		{
			(*input)[pars->start] = '\"';
			(*input)[pars->end] = '\"';
		}
		free(pars->str);
		pars->str = NULL;
		pars->start = pars->end;
	}
	pars->i++;
}

// in some cases the single quote act exactly like double quotes ...
// then should i replace them in that case ?
void	should_i_replace_them(char **input)
{
	t_parse	*pars;

	pars = malloc(sizeof(t_parse));
	pars->start = 0;
	pars->end = 0;
	pars->taken = 1;
	pars->i = 0;
	while ((*input)[pars->i])
		search_and_replace(pars, input);
	free(pars);
}

void	i_should_replace_single(t_parse *pars, char **input)
{
	if ((*input)[pars->i] == '\'' && pars->taken == 1)
	{
		pars->start = pars->i;
		pars->taken = 0;
	}
	else if ((*input)[pars->i] == '\'' && pars->taken == 0)
	{
		pars->end = pars->i;
		pars->taken = 1;
	}
	if (pars->start < pars->end)
	{
		pars->str = take_copy((*input), pars->start, pars->end);
		if (!char_counter(pars->str, '\"'))
		{
			(*input)[pars->start] = '\"';
			(*input)[pars->end] = '\"';
		}
		free(pars->str);
		pars->str = NULL;
		pars->start = pars->end;
	}
	pars->i++;
}

// i mean the name is really clear
void	i_should_replace_them(char **input)
{
	t_parse	*pars;

	pars = malloc(sizeof(t_parse));
	pars->start = 0;
	pars->end = 0;
	pars->taken = 1;
	pars->i = 0;
	while ((*input)[pars->i])
		i_should_replace_single(pars, input);
	free(pars);
}
