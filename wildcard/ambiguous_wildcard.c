/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:24:28 by admansar          #+#    #+#             */
/*   Updated: 2023/06/12 12:28:46 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	the_checker(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		if (i > 0 && !ft_strcmp ((*split)[i], "*")
				&& (!ft_strncmp ((*split)[i - 1], "<<", 2)))
			(*split)[i] = ft_str_join ((*split)[i], "\3");
		if (i > 0 && !ft_strcmp ((*split)[i], "*")
				&& (!ft_strncmp ((*split)[i - 1], ">", 1)
					|| ((*split)[i - 1][0] == '<'
					&& (*split)[i - 1][1] != '<')
					|| !ft_strncmp ((*split)[i - 1], ">>", 2)))
			(*split)[i] = ft_str_join ((*split)[i], "\a");
		i++;
	}
}
