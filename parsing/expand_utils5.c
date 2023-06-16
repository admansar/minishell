/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:12:16 by admansar          #+#    #+#             */
/*   Updated: 2023/06/16 16:11:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_expanding(t_expand *expand, char ***str_pro_max, char **env)
{
	(*expand).start = (*expand).j;
	while ((*str_pro_max)[(*expand).i][(*expand).j]
			&& (ft_isalpha((*str_pro_max)[(*expand).i][(*expand).j + 1])
				|| ft_isdigit((*str_pro_max)[(*expand).i][(*expand).j + 1])
				|| (*str_pro_max)[(*expand).i][(*expand).j + 1] == '_'))
		(*expand).j++;
	(*expand).end = (*expand).j;
	(*expand).tmp = take_copy((*str_pro_max)[(*expand).i], (*expand).start + 1,
			(*expand).end);
	(*expand).k = -1;
	while (env[++(*expand).k])
	{
		(*expand).h = ft_strlen((*expand).tmp);
		if (!ft_strncmp((*expand).tmp, env[(*expand).k], (*expand).h)
			&& env[(*expand).k][(*expand).h] == '=')
		{
			(*expand).tmp2 = take_variable_from_env(env, (*expand).k,
					(*str_pro_max)[(*expand).i], (*expand).h);
			store_after_expand_var((*expand).tmp2, &(*expand).m,
				&((*expand).str)[(*expand).i]);
			break ;
		}
	}
	(*expand).m--;
	free((*expand).tmp);
}

void	expand_exit_stat(t_expand *expand, char **env)
{
	(*expand).tmp = ft_strdup("?");
	(*expand).j++;
	(*expand).k = 0;
	(*expand).h = ft_strlen((*expand).tmp);
	while (env[(*expand).k])
	{
		if (!ft_strncmp((*expand).tmp, env[(*expand).k], (*expand).h)
			&& env[(*expand).k][(*expand).h] == '=')
		{
			(*expand).tmp2 = take_copy(env[(*expand).k], (*expand).h + 1,
					ft_strlen(env[(*expand).k]));
			(*expand).k = 0;
			while ((*expand).tmp2[(*expand).k])
				(*expand).str[(*expand).i][(*expand).m++]
					= (*expand).tmp2[(*expand).k++];
			free((*expand).tmp2);
			break ;
		}
		(*expand).k++;
	}
	(*expand).m--;
	free((*expand).tmp);
}

void	creat_the_expanded_copy(t_expand *expand,
char ***str_pro_max, char **env)
{
	if ((*str_pro_max)[(*expand).i][(*expand).j] == '$'
			&& ((*str_pro_max)[(*expand).i][(*expand).j + 1] == '@'
				|| ft_isdigit((*str_pro_max)[(*expand).i][(*expand).j + 1])))
		(*expand).j += 2;
	if ((*str_pro_max)[(*expand).i][(*expand).j] == '$'
			&& (ft_isalpha((*str_pro_max)[(*expand).i][(*expand).j + 1])
				|| (*str_pro_max)[(*expand).i][(*expand).j + 1] == '_'
				|| ft_isdigit((*str_pro_max)[(*expand).i][(*expand).j
					+ 1])))
		start_expanding(&(*expand), str_pro_max, env);
	else if ((*str_pro_max)[(*expand).i][(*expand).j] == '$'
			&& ((*str_pro_max)[(*expand).i][(*expand).j + 1] == '?'))
		expand_exit_stat(&(*expand), env);
	else
		(*expand).str[(*expand).i][(*expand).m]
			= (*str_pro_max)[(*expand).i][(*expand).j];
	(*expand).j++;
	(*expand).m++;
}

void	fill_str(t_expand *expand, char ***str_pro_max, char **env)
{
	while ((*str_pro_max)[(*expand).i])
	{
		(*expand).j = 0;
		(*expand).m = 0;
		while ((*str_pro_max)[(*expand).i][(*expand).j])
		{
			creat_the_expanded_copy(expand, str_pro_max, env);
		}
		if (char_counter ((*str_pro_max)[(*expand).i], '\6'))
			disable (&(*str_pro_max)[(*expand).i], '\6');
		(*expand).i++;
	}
}

void	expand_after_redirections(t_expand *expand, char ***str_pro_max,
		char **env)
{
	if (mega_counter((*str_pro_max), '\'') || mega_counter((*str_pro_max),
			'\"'))
	{
		while ((*expand).j > 0)
		{
			(*expand).h = ft_strlen((*str_pro_max)[(*expand).j]) - 1;
			if ((*expand).h >= 0 && (*str_pro_max)[(*expand).j][(*expand).h
					- 1] == ' ')
				break ;
			(*expand).j--;
		}
	}
	if ((*expand).j >= 0 && (*expand).j != (*expand).i)
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
				(*str_pro_max)[(*expand).j], env);
	else if ((*expand).i > 0)
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
				(*str_pro_max)[(*expand).i - 1], env);
	else
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
				NULL, env);
}
