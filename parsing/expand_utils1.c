/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:08:54 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:40:30 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_to_allocate(char **str)
{
	return (ft_strlen((*str)) + (char_counter((*str), '>') * 2)
		+ (char_counter((*str), '<') * 2) + (char_counter((*str), '|') * 2)
		+ 1);
}

// making space to let the "rederections"
// easy to detect inside by the ultra_split
void	make_some_space(char **str)
{
	char	*tmp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!((char_counter((*str), '>')) || (char_counter((*str), '<'))
			|| (char_counter((*str), '|'))))
		return ;
	tmp = ft_calloc(sizeof(char), size_to_allocate(str));
	while ((*str)[i])
		if ((*str)[i] == '>' && (*str)[i + 1] == '>')
			space_append_heardoc(&tmp, &i, &j, 2);
	else if ((*str)[i] == '>')
		space_char(&tmp, &i, &j, '>');
	else if ((*str)[i] == '|')
		space_char(&tmp, &i, &j, '|');
	else if ((*str)[i] == '<' && (*str)[i + 1] == '<')
		space_append_heardoc(&tmp, &i, &j, 4);
	else if ((*str)[i] == '<')
		space_char(&tmp, &i, &j, '<');
	else
		tmp[j++] = (*str)[i++];
	free((*str));
	(*str) = tmp;
}

// wanna make a copy of your double array ,
// use fill function ... its your friend

int	in_env(char *ptr, char **env, int flag)
{
	static char	**the_env;
	int			k;

	k = -1;
	if (flag == 1)
	{
		if (!the_env)
			the_env = fill(env);
		else if (env)
		{
			free_double_array(the_env);
			the_env = fill(env);
		}
		return (-2);
	}
	while (the_env[++k])
		if (!ft_strncmp(the_env[k], ptr, ft_strlen(ptr))
			&& the_env[k][ft_strlen(ptr)] == '=')
			return (k);
	return (-1);
}

int	checking_direction_expand(char *str, char **env)
{
	int		end;
	char	*tmp;

	end = ft_simularity_len(str, '$');
	while (str[end + 1] && (ft_isalpha(str[end + 1]) || ft_isdigit((str[end
						+ 1])) || (str[end + 1] == '_')))
		end++;
	tmp = take_copy(str, ft_simularity_len(str, '$') + 1, end);
	end = in_env(tmp, NULL, 0);
	if (end >= 0)
	{
		if (!char_counter(env[end], ' '))
		{
			free(tmp);
			return (1);
		}
	}
	else
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}
