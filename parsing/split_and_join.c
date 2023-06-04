/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:04:06 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:18:59 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_space_split_join(char **new_str, char ***split, int i)
{
	make_some_space(&(new_str)[i]);
	(*split) = my_spliter(new_str[i], 0, 0, 0);
	if (new_str[i][ft_strlen(new_str[i]) - 1] == ' ')
		(*split)[ft_strcount(*split)
			- 1] = ft_str_join((*split)[ft_strcount(*split) - 1], " ");
}

// the best split for the project
char	**ultra_split(char **new_str, char **input)
{
	char	**split;
	char	**str_pro_max;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	str_pro_max = ft_calloc(sizeof(char *), ft_strlen((*input)));
	while (new_str[++i])
	{
		if (!surounded_by(new_str[i], '\"') && char_counter(new_str[i], ' ')
			&& !surounded_by(new_str[i], '\''))
		{
			make_space_split_join(new_str, &split, i);
			j = 0;
			while (split[j])
				str_pro_max[k++] = ft_strdup(split[j++]);
			free_double_array(split);
		}
		else
			str_pro_max[k++] = ft_strdup(new_str[i]);
	}
	return (str_pro_max);
}

void	delete_array_form_double_array(int *i, char ***str_pro_max)
{
	int	j;

	j = (*i) + 1;
	while ((*str_pro_max)[j + 1])
	{
		free((*str_pro_max)[j]);
		(*str_pro_max)[j] = ft_strdup((*str_pro_max)[j + 1]);
		j++;
	}
	free((*str_pro_max)[j]);
	(*str_pro_max)[j] = NULL;
	(*i) = -1;
}

// join the string to the next one that should be joined with
void	the_joiner(char ***str_pro_max)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	if (i + 1 < ft_strcount(*str_pro_max))
	{
		while ((*str_pro_max)[i + 1])
		{
			h = ft_strlen((*str_pro_max)[i]) - 1;
			if ((*str_pro_max)[i][h] != ' ' && (*str_pro_max)[i
					+ 1][0] != '>' && (*str_pro_max)[i + 1][0] != '<'
					&& (*str_pro_max)[i + 1][0] != '|')
			{
				if (char_counter((*str_pro_max)[i + 1], '$')
						&& surounded_by((*str_pro_max)[i + 1], '\''))
					exchange(&(*str_pro_max)[i + 1], '\'', '\"');
				(*str_pro_max)[i] = ft_str_join((*str_pro_max)[i],
						(*str_pro_max)[i + 1]);
				delete_array_form_double_array(&i, str_pro_max);
			}
			i++;
		}
	}
}
