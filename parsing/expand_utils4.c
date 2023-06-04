/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:11:35 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:32:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_from_env(char ***str_pro_max, char **env, int i, int *j)
{
	int		start;
	int		k;
	int		h;
	int		end;
	char	*tmp;

	start = (*j);
	while ((*str_pro_max)[i][(*j)] && (ft_isalpha((*str_pro_max)[i][(*j) + 1])
			|| ft_isdigit((*str_pro_max)[i][(*j) + 1])
			|| (*str_pro_max)[i][(*j) + 1] == '_'))
		(*j)++;
	end = (*j);
	tmp = take_copy((*str_pro_max)[i], start + 1, end);
	k = -1;
	h = ft_strlen(tmp);
	while (env[++k])
	{
		if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
		{
			k = ft_strlen(env[k]);
			break ;
		}
	}
	free(tmp);
	return (k);
}

int	len_from_env_(char **env, int *j)
{
	char	*tmp;
	int		k;
	int		h;

	tmp = ft_strdup("?");
	(*j)++;
	k = 0;
	h = ft_strlen(tmp);
	while (env[k])
	{
		if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
		{
			k = ft_strlen(env[k]);
			break ;
		}
		k++;
	}
	free(tmp);
	return (k);
}

int	get_len_to_allocate(char ***str_pro_max, int i, char **env)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while ((*str_pro_max)[i][j])
	{
		if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j + 1] == '@'
					|| ft_isdigit((*str_pro_max)[i][j + 1])))
			delete_them(&(*str_pro_max)[i], j, j + 1);
		if ((*str_pro_max)[i][j] == '$' && (ft_isalpha((*str_pro_max)[i][j + 1])
					|| (*str_pro_max)[i][j + 1] == '_'
					|| ft_isdigit((*str_pro_max)[i][j + 1])))
			k = len_from_env(&(*str_pro_max), env, i, &j);
		else if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j
					+ 1] == '?'))
			k = len_from_env_(env, &j);
		else
			j++;
		if (j >= (int)ft_strlen((*str_pro_max)[i]))
			break ;
	}
	return (k + ft_strlen((*str_pro_max)[i]));
}

void	get_size_to_expand(char ***str, char ***str_pro_max, char **env)
{
	int	i;

	i = 0;
	(*str) = ft_calloc(sizeof(char *), (ft_strcount(*str_pro_max) + 1));
	while ((*str_pro_max)[i])
	{
		(*str)[i] = ft_calloc(sizeof(char), (get_len_to_allocate(str_pro_max, i,
						env) + 1) * (char_counter((*str_pro_max)[i], '$') + 3));
		i++;
	}
}

char	*take_variable_from_env(char **env, int k, char *str_pro_max, int h)
{
	char	*tmp2;

	tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
	if (surounded_by(str_pro_max, '\"'))
		exchange(&tmp2, ' ', '\5');
	no_extra_(&tmp2, ' ');
	replace_spaces(&tmp2);
	tmp2 = ft_str_join(tmp2, "\2");
	return (tmp2);
}
