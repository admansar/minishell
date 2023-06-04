/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:10:34 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:33:24 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exit_stat_size(t_expand *expand, char **env)
{
	expand->tmp = ft_strdup("?");
	expand->i++;
	expand->k = 0;
	expand->h = ft_strlen(expand->tmp);
	while (env[expand->k])
	{
		if (!ft_strncmp(expand->tmp, env[expand->k], expand->h)
			&& env[expand->k][expand->h] == '=')
		{
			expand->k = ft_strlen(env[expand->k]);
			break ;
		}
		expand->k++;
	}
	free(expand->tmp);
}

void	the_expander(t_expand *expand, char **ptr, char **env)
{
	expand->start = expand->i;
	while ((*ptr)[expand->i] && (ft_isalpha((*ptr)[expand->i + 1])
				|| ft_isdigit((*ptr)[expand->i + 1]) || (*ptr)[expand->i
				+ 1] == '_'))
		expand->i++;
	expand->end = expand->i;
	expand->tmp = take_copy((*ptr), expand->start + 1, expand->end);
	expand->k = -1;
	expand->h = ft_strlen(expand->tmp);
	while (env[++expand->k])
	{
		if (!ft_strncmp(env[expand->k], expand->tmp, expand->h)
			&& env[expand->k][expand->h] == '=')
		{
			expand->tmp2 = take_copy(env[expand->k], expand->h + 1,
					ft_strlen(env[expand->k]));
			expand->k = 0;
			while (expand->tmp2[expand->k])
				expand->re[expand->j++] = expand->tmp2[expand->k++];
			free(expand->tmp2);
			break ;
		}
	}
	expand->j--;
	free(expand->tmp);
}

void	expand_exit_stat_array(t_expand *expand, char **env)
{
	expand->tmp = ft_strdup("?");
	expand->i++;
	expand->k = 0;
	expand->h = ft_strlen(expand->tmp);
	while (env[expand->k])
	{
		if (!ft_strncmp(expand->tmp, env[expand->k], expand->h)
			&& env[expand->k][expand->h] == '=')
		{
			expand->tmp2 = take_copy(env[expand->k], expand->h + 1,
					ft_strlen(env[expand->k]));
			expand->k = 0;
			while (expand->tmp2[expand->k])
				expand->re[expand->j++] = expand->tmp2[expand->k++];
			free(expand->tmp2);
			break ;
		}
		expand->k++;
	}
	expand->j--;
	free(expand->tmp);
}

void	time_to_expand(t_expand *expand, char **ptr, char **env)
{
	expand->re = malloc(sizeof(char) * (ft_strlen((*ptr)) + expand->k + 1)
			* (char_counter((*ptr), '$') + 1));
	expand->i = 0;
	expand->j = 0;
	while ((*ptr)[expand->i])
	{
		if ((*ptr)[expand->i] == '$' && (ft_isalpha((*ptr)[expand->i + 1])
					|| ft_isdigit((*ptr)[expand->i + 1]) || (*ptr)[expand->i
					+ 1] == '_'))
			the_expander(expand, ptr, env);
		else if ((*ptr)[expand->i] == '$' && (*ptr)[expand->i + 1] == '?')
			expand_exit_stat_array(expand, env);
		else
			expand->re[expand->j] = (*ptr)[expand->i];
		expand->j++;
		expand->i++;
	}
	expand->re[expand->j] = '\0';
}

void	array_expander(char **ptr, char **env)
{
	t_expand	*expand;

	expand = malloc(sizeof(t_expand));
	expand->i = 0;
	expand->k = 0;
	while ((*ptr)[expand->i])
	{
		if ((*ptr)[expand->i] == '$' && (ft_isalpha((*ptr)[expand->i + 1])
					|| ft_isdigit((*ptr)[expand->i + 1]) || (*ptr)[expand->i
					+ 1] == '_'))
			the_array_size_to_expand(expand, ptr, env);
		else if ((*ptr)[expand->i] == '$' && (*ptr)[expand->i + 1] == '?')
			expand_exit_stat_size(expand, env);
		expand->i++;
	}
	time_to_expand(expand, ptr, env);
	free(*ptr);
	*ptr = ft_strdup(expand->re);
	free(expand->re);
	free(expand);
}
