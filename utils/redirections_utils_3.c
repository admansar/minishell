/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:14 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/05 23:29:55 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_outfile_nbr(t_files *f_data, t_input *list, t_redir *data)
{
	data->count = 0;
	f_data->i = 0;
	while (list->redirect->type[f_data->i])
	{
		if (!ft_strcmp(list->redirect->type[f_data->i], OUTPUT))
			data->count++;
		else if (!ft_strcmp(list->redirect->type[f_data->i], APPEND))
			data->count++;
		f_data->i++;
	}
}

int	ft_check_permissions(t_input *list, t_redir *data, t_files *f_data,
		int flag)
{
	if (!ft_is_file_dir(list, data, f_data))
		return (0);
	f_data->ret = access(list->redirect->file_name[f_data->i], R_OK | W_OK);
	if (!f_data->ret)
	{
		data->out_fd = open(list->redirect->file_name[f_data->i],
				O_RDWR | flag, 0644);
		f_data->j++;
		if (f_data->j < data->count)
			close(data->out_fd);
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
	data->out_fd = open(list->redirect->file_name[f_data->i],
			O_RDWR | O_CREAT | flag, 0644);
	f_data->j++;
	if (f_data->j < data->count)
		close(data->out_fd);
	if (data->output <= f_data->i)
		data->output = f_data->i;
}
