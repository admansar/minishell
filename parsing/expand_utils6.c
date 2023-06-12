/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:12:12 by admansar          #+#    #+#             */
/*   Updated: 2023/06/12 22:12:16 by admansar         ###   ########.fr       */
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
