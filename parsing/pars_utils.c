/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:21:32 by admansar          #+#    #+#             */
/*   Updated: 2023/06/12 19:29:08 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_it(char **copy, char ***env, char ***split)
{
	int	check;

	if (char_counter((*copy), '\"') || char_counter((*copy), '\''))
		(*split) = parsing(&(*copy), *env);
	else
	{
		make_some_space(&(*copy));
		(*split) = ft_split((*copy), ' ');
		expand(&(*split), *env);
		split_and_join(&(*split));
	}
	check = last_check((*split));
	if (check == -2)
		(*split) = NULL;
	if (check != -1 && (*split))
	{
		if (check + 1 < ft_strcount((*split)))
			ft_printf("bash: syntax error near unexpected token `%s'\n",
				(*split)[check + 1]);
		else
			ft_printf("bash: syntax error near unexpected token `newline'\n");
		g_vars.g_exit_status = 2;
		free_double_array((*split));
		(*split) = NULL;
	}
}

void	parse_phil_list_and_excute(char **copy, char ***env, char ***export)
{
	char	**split;
	t_input	*list;

	if (fast_check((*copy)))
	{
		parse_it(&(*copy), env, &split);
		ft_update_exit_status(env);
		if (split)
		{
			if (mega_counter(split, '*'))
				wildcard(&split);
			list = work_time(split);
			free_double_array(split);
			ft_execution(list, env, export);
			ft_update_exit_status(env);
			ft_update_last_command(env, list);
			free_list(list);
		}
	}
}

int	catch_you(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "<<", 2) && str[i + 1]
			&& !ft_strncmp(str[i + 1], "<", 1))
			return (i);
		if (!ft_strncmp(str[i], ">>", 2) && str[i + 1]
			&& !ft_strncmp(str[i + 1], ">", 1))
			return (i);
		if (!ft_strncmp(str[i], "|", 1) && str[i + 1]
			&& !ft_strncmp(str[i + 1], "|", 1))
			return (i);
		i++;
	}
	return (-1);
}
