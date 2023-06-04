/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:12 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/03 20:18:13 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ambiguous(t_input *list, t_redir *data, int i)
{
	if (!list->redirect->file_name[i])
		ft_error(data, AMBIGUOUS_ERR);
	if (list->redirect->file_name[i]
		&& char_counter(list->redirect->file_name[i], '\a'))
		ft_error(data, AMBIGUOUS_ERR);
	if (list->redirect->file_name[i] && list->redirect->file_name[i][0] == '\0')
		ft_error(data, NO_FILE);
	if (list->redirect->file_name[i] && list->redirect->file_name[i][0] == '\2')
		ft_error(data, AMBIGUOUS_ERR);
	if (data->error)
		return (1);
	return (0);
}

int	ambiguous_check_1(t_input *list, t_redir *data, int i)
{
	if (((ft_strlen(list->redirect->file_name[i]) == 1)
			&& list->redirect->file_name[i][0] == '\2'))
	{
		ft_error(data, AMBIGUOUS);
		return (1);
	}
	return (0);
}

int	ambiguous_check_2(t_input *list, t_redir *data, char *tmp, int i)
{
	if (ft_char_checker(list->redirect->file_name[i], '\4') >= 0)
	{
		ft_error(data, AMBIGUOUS);
		free(tmp);
		return (1);
	}
	else if (char_counter(list->redirect->file_name[i], '\1') && (inside_of(tmp,
				'\1') || consecutive(tmp, '\1') || ft_strlen(tmp) == 1))
	{
		ft_error(data, AMBIGUOUS);
		free(tmp);
		return (1);
	}
	return (0);
}

// check if there is an ambiguous redirection
int	ft_early_ambiguous_check(t_input *list, t_redir *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (list->redirect->file_name[++i])
	{
		if (ambiguous_check_1(list, data, i))
			return (1);
		tmp = clean_from(list->redirect->file_name[i], '\2');
		if (ambiguous_check_2(list, data, tmp, i))
			return (1);
		else if (ft_char_checker(tmp, '\1') >= 0)
		{
			disable(&list->redirect->file_name[i], '\1');
			disable(&list->redirect->file_name[i], '\2');
		}
		free(tmp);
	}
	return (0);
}

void	ft_error(t_redir *data, int flag)
{
	if (flag == AMBIGUOUS)
	{
		ft_printf("minishell: ambiguous redirect\n");
		g_vars.g_exit_status = 1;
	}
	else if (flag == AMBIGUOUS_ERR)
	{
		ft_printf("minishell: ambiguous redirect\n");
		g_vars.g_exit_status = 1;
		data->error = 1;
	}
	else if (flag == NO_FILE)
	{
		ft_printf("minishell: No such file or directory\n");
		g_vars.g_exit_status = 1;
		data->error = 1;
	}
}
