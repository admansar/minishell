/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:14 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/04 11:27:19 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_all_fds(t_files *f_data, t_input *list, t_redir *data)
{
	f_data->ret = 0;
	f_data->i = -1;
	while (list->redirect->type[++f_data->i])
	{
		if (!strcmp(list->redirect->type[f_data->i], OUTPUT))
			data->count++;
		else if (!ft_strcmp(list->redirect->type[f_data->i], APPEND))
			data->count++;
	}
	f_data->arr = ft_calloc(sizeof(int), (data->count + 3));
	f_data->i = -1;
	f_data->j = 0;
}

int	ft_check_permissions(t_input *list, t_redir *data, t_files *f_data,
		int flag)
{
	f_data->ret = access(list->redirect->file_name[f_data->i], R_OK | W_OK);
	if (!f_data->ret)
	{
		f_data->arr[f_data->j++] = open(list->redirect->file_name[f_data->i],
				O_RDWR | flag, 0644);
		if (data->output <= f_data->i)
			data->output = f_data->i;
	}
	else if (f_data->ret == -1)
	{
		ft_printf("minishell: %s: %s\n", list->redirect->file_name[f_data->i],
			strerror(errno));
		data->error = 1;
		g_vars.g_exit_status = 1;
		return (0);
	}
	return (1);
}

int	file_found(t_input *list, t_files *f_data)
{
	if (!access(list->redirect->file_name[f_data->i], F_OK))
		return (1);
	return (0);
}

void	ft_create_file(t_input *list, t_redir *data, t_files *f_data, int flag)
{
	f_data->arr[f_data->j++] = open(list->redirect->file_name[f_data->i],
			O_RDWR | O_CREAT | flag, 0644);
	if (data->output <= f_data->i)
		data->output = f_data->i;
}

void	get_out_fd(t_files *f_data, t_redir *data)
{
	if (f_data->j > 0)
		data->out_fd = f_data->arr[f_data->j - 1];
	f_data->j = 0;
	while (f_data->j < data->count - 1)
		close(f_data->arr[f_data->j++]);
	free(f_data->arr);
}
