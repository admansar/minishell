/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:09:36 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:37:28 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	recursive_why_not(char *str, char **env)
{
	int		i;
	char	**split;
	int		end;

	split = ft_split(str, ' ');
	i = -1;
	end = 1;
	while (split[++i])
	{
		if (char_counter(split[i], '$'))
		{
			if (i > 0)
				end = checking_direction(split[i], split[i - 1], env);
			else
				end = checking_direction(split[i], NULL, env);
			break ;
		}
	}
	free_double_array(split);
	return (end);
}

int	recursive_untill_found(char *str, char **env)
{
	char	**split;
	int		i;
	int		end;

	end = 1;
	split = ft_split(str, ' ');
	i = -1;
	while (split[++i])
	{
		if (char_counter(split[i], '$'))
		{
			if (i > 0)
			{
				end = checking_direction(split[i], split[i - 1], env);
				break ;
			}
		}
	}
	free_double_array(split);
	return (end);
}

int	checking_direction(char *str, char *behind_str, char **env)
	// this function take a look the expand to make it more exact ...
{
	if (behind_str)
	{
		if (!surounded_by(str, '\'') && (!ft_strncmp(behind_str
					+ ft_simularity_len(behind_str, '<'), "<<", 2)))
			return (2);
		else if (!surounded_by(str, '\'') && !surounded_by(str, '\"')
			&& !char_counter(str, ' ') && (!ft_strncmp(behind_str, ">>", 2)
				|| !ft_strncmp(behind_str, "<", 1) || !ft_strncmp(behind_str,
					">", 1)))
			return (checking_direction_expand(str, env));
		else if (!surounded_by(str, '\'') && !surounded_by(str, '\"')
			&& char_counter(str, ' '))
			return (recursive_why_not(str, env));
	}
	else if (!surounded_by(str, '\'') && !surounded_by(str, '\"')
		&& char_counter(str, ' '))
		return (recursive_untill_found(str, env));
	return (1);
}

void	replace_spaces(char **ptr)
{
	int	i;
	int	h;

	i = 0;
	h = ft_strlen(*ptr) - 1;
	if ((*ptr[i]) == ' ')
	{
		(*ptr)[i] = '\1';
		i++;
	}
	if (h > 0 && (*ptr)[h] == ' ')
		(*ptr)[h] = '\1';
	while ((*ptr)[i])
	{
		if ((*ptr)[i] == ' ')
			(*ptr)[i] = '\4';
		i++;
	}
}

void	the_array_size_to_expand(t_expand *expand, char **ptr, char **env)
{
	expand->start = expand->i;
	while ((*ptr)[expand->i] && (ft_isalpha((*ptr)[expand->i + 1])
				|| ft_isdigit((*ptr)[expand->i + 1]) || (*ptr)[expand->i
				+ 1] == '_'))
		expand->i++;
	expand->end = expand->i;
	expand->tmp = take_copy((*ptr), expand->start + 1, expand->end);
	expand->k = 0;
	while (env[expand->k])
	{
		expand->h = ft_strlen(expand->tmp);
		if (!ft_strncmp(env[expand->k], expand->tmp, expand->h)
			&& env[expand->k][expand->h] == '=')
		{
			expand->k = ft_strlen(env[expand->k]);
			break ;
		}
		expand->k++;
	}
	free(expand->tmp);
}
