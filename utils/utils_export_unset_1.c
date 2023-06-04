/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_unset_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:17 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/04 15:03:09 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_name_checker(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	ft_export_name_checker(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'
			|| str[i] == '=' || (str[i] == '+' && (str[i + 1] == '='
					|| str[i + 1] == '\0')))
			i++;
		else
			return (-1);
	}
	return (0);
}

void	ft_cases_printer(char **export, t_export *data)
{
	if (export[data->i][0] == '?' && export[data->i][1] == '=')
		data->i++;
	else if (ft_char_checker(export[data->i], '=') == -1)
	{
		printf("declare -x %s\n", data->tmp1);
		data->i++;
	}
	else
	{
		printf("declare -x %s=\"", data->tmp1);
		data->j = 0;
		while (data->tmp2[data->j])
		{
			if (data->tmp2[data->j] == '$' || data->tmp2[data->j] == '\"')
				printf("\\");
			printf("%c", data->tmp2[data->j++]);
		}
		printf("\"\n");
		data->i++;
	}
}

void	ft_export_printer(t_input *list, char **export, t_export *data)
{
	if (list->arg[0])
		return ;
	data->i = 0;
	while (export[data->i])
	{
		data->len = ft_simularity_len(export[data->i], '=');
		data->tmp1 = take_copy(export[data->i], 0, data -> len - 1);
		data->tmp2 = take_copy(export[data->i], data -> len + 1,
				ft_strlen(export[data->i]));
		ft_cases_printer(export, data);
		free(data->tmp1);
		free(data->tmp2);
	}
}

// search for a '+' in my str and create new str that does not contain the '+'
void	ft_clean_up_name(char **str)
{
	int		i;
	int		ret;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while (str[i])
	{
		ret = ft_char_checker(str[i], '+');
		if (ret >= 0)
		{
			tmp = take_copy(str[i], 0, ret - 1);
			tmp1 = take_copy(str[i], ret + 1, ft_strlen(str[i]));
			free(str[i]);
			str[i] = ft_strjoin(tmp, tmp1);
			free(tmp);
			free(tmp1);
		}
		i++;
	}
}
