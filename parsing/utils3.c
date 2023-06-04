/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:56:03 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:13:32 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// d for double quotes
void	d_delete(char **input)
{
	t_parse	*pars;

	pars = malloc(sizeof(t_parse));
	pars->i = 0;
	pars->taken = 1;
	pars->start = 0;
	pars->end = 0;
	pars->len = ft_strlen(*input) + 1;
	while ((*input)[pars->i])
	{
		pars->used = 0;
		if ((*input)[pars->i] == '\"' && pars->taken == 1)
		{
			pars->start = pars->i;
			pars->taken = 0;
		}
		else if ((*input)[pars->i] == '\"' && pars->taken == 0)
		{
			pars->end = pars->i;
			pars->taken = 1;
		}
		delete_both_double(pars, input);
		pars->i++;
	}
	free(pars);
}

void	delete_both_single(t_parse *pars, char **input)
{
	if (pars->start == pars->end - 1)
	{
		if (pars->start > 0)
			if ((*input)[pars->start - 1] == ' ')
				pars->used = 0.5;
		if (pars->end < pars->len)
			if ((*input)[pars->end + 1] == ' ' || pars->end + 1 == pars->len)
				pars->used += 0.5;
		if (pars->used != 1)
		{
			delete_both(input, pars->start, pars->end, '\'');
			pars->i = -1;
			pars->start = 0;
			pars->end = 0;
			pars->taken = 1;
		}
	}
}

// s for single quotes
void	s_delete(char **input)
{
	t_parse	*pars;

	pars = malloc(sizeof(t_parse));
	pars->i = 0;
	pars->taken = 1;
	pars->start = 0;
	pars->end = 0;
	pars->len = ft_strlen(*input) + 1;
	while ((*input)[pars->i])
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
		delete_both_single(pars, input);
		pars->i++;
	}
	free(pars);
}

void	look_for_partner(t_parse *pars, char ***new_str, char **input)
{
	(*new_str)[pars->j] = ft_calloc(sizeof(char), (ft_strlen((*input)) + 1));
	pars->k = 0;
	while ((*input)[pars->i] && (*input)[pars->i] != '\''
		&& (*input)[pars->i] != '\"')
	{
		(*new_str)[pars->j][pars->k] = (*input)[pars->i];
		pars->k++;
		pars->i++;
	}
	(*new_str)[pars->j][pars->k] = '\0';
	should_i_replace_them(&(*new_str)[pars->j]);
	make_some_space(&(*new_str)[pars->j]);
	pars->j++;
	pars->i--;
}

// no need to the comment !!
// anyway this function delete the double qoutes that start and
// end with nothing inside
void	delete_non_sense(char **input)
{
	(*input) = ft_str_join((*input), " ");
	d_delete(input);
	s_delete(input);
}
