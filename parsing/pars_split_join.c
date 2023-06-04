/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_split_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:20:08 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:25:30 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	re_split(char ***tmp, char **split, int *j)
{
	char	**ptr;
	int		k;

	if (char_counter((*split), ' '))
	{
		ptr = ft_split((*split), ' ');
		k = 0;
		while (ptr[k])
			(*tmp)[(*j)++] = ptr[k++];
		free(ptr);
		if ((*j) > 0)
			(*j)--;
	}
	else
		(*tmp)[(*j)] = (*split);
}

void	split_and_join(char ***split)
{
	int		i;
	int		j;
	char	**tmp;

	if (!(*split))
		return ;
	tmp = ft_calloc(sizeof(char *), ft_strcount((*split)) + mega_counter(*split,
				' ') + 2);
	i = 0;
	j = 0;
	while ((*split)[i])
	{
		re_split(&tmp, &(*split)[i], &j);
		j++;
		i++;
	}
	free(*split);
	*split = tmp;
}

int	last_check(char **str)
{
	int	i;
	int	h;

	i = -1;
	if (!str)
		return (-1);
	if (!str[i + 1])
	{
		free_double_array(str);
		return (-2);
	}
	while (str[++i + 1])
		if (check_error(str, i) != -1)
			return (i);
	h = ft_strlen(str[i]);
	if (h > 0)
	{
		if (str[i][h - 1] == '>')
			return (i);
		if (str[i][h - 1] == '<')
			return (i);
	}
	return (-1);
}

// the best one to use till moument
// te perfect parsing does not exis ...
char	**parsing(char **input, char **env)
{
	char	**new_str;
	char	**str_pro_max;

	new_str = split_without_weast(input);
	if (ft_strlen((*input)) && !ft_strcount(new_str))
	{
		error_print("bash: unexpected EOF while looking for matching", NULL);
		g_vars.g_exit_status = 2;
		free_double_array(new_str);
		return (NULL);
	}
	expand(&new_str, env);
	str_pro_max = ultra_split(new_str, input);
	free_double_array(new_str);
	the_joiner(&str_pro_max);
	no_etxra_qoutes(&str_pro_max);
	return (str_pro_max);
}

void	split_without_weast_utils(t_parse *pars, char ***new_str, char **input)
{
	if (((*input)[pars->i] == '\"' || (*input)[pars->i] == '\'')
			&& pars->taken == 1)
	{
		pars->start = pars->i;
		pars->taken = 0;
	}
	else if (pars->taken == 1)
		look_for_partner(pars, new_str, input);
	else if (((*input)[pars->i] == '\"' || (*input)[pars->i] == '\'')
			&& pars->taken == 0 && (*input)[pars->start] == ((*input)[pars->i]))
	{
		pars->end = pars->i;
		if ((*input)[pars->i + 1] == ' ')
			pars->end = ++pars->i;
		pars->taken = 1;
	}
	if (pars->start < pars->end)
	{
		(*new_str)[pars->j++] = take_copy((*input), pars->start, pars->end);
		if (!surounded_by((*new_str)[pars->j - 1], '\"'))
			should_i_replace_them(&(*new_str)[pars->j - 1]);
		pars->start = pars->end;
	}
	pars->i++;
}
