/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:57 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/04 15:07:43 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_join_path_and_cmd(t_input *list, t_execution *data, char ***envi)
{
	if (list->arg[0])
	{
		if (list->arg[0][0] == '\0')
		{
			free(list->arg[0]);
			list->arg[0] = NULL;
		}
	}
	data->tmp = take_copy((*envi)[data->inside],
			ft_simularity_len((*envi)[data->inside], '=') + 1,
			ft_strlen((*envi)[data->inside]));
	data->env = ft_split(data->tmp, ':');
	free(data->tmp);
	data->acces = ft_calloc(sizeof(char *), ft_strcount(data->env) + 1);
	data->i = 0;
	while (data->env[data->i])
	{
		data->tmp = ft_strjoin("/", list->cmd);
		data->acces[data->i] = ft_strjoin(data->env[data->i], data->tmp);
		free(data->tmp);
		data->i++;
	}
}

void	ft_check_access(t_execution *data)
{
	data->i = 0;
	data->found = 0;
	while (data->acces[data->i])
	{
		if (access(data->acces[data->i], F_OK | X_OK) + 1)
		{
			data->found = 1;
			break ;
		}
		data->i++;
	}
}

t_input	*ft_skip_same_cmd(t_input *list)
{
	t_input	*tmp;

	tmp = list;
	while (list->next)
	{
		if (!ft_strcmp(list->cmd, list->next->cmd) && !list->redirect->position
			&& !list->arg[0] && !list->next->arg[0])
		{
			tmp = list->next;
		}
		else
			break ;
		list = list->next;
	}
	return (tmp);
}

int	ft_check_pipe_errors(t_input *list, t_pipe *pipe_data, char ***envi,
		char ***export)
{
	if (pipe_data->pipe_num == 0)
	{
		ft_exec(list, envi, export);
		return (1);
	}
	if (pipe_data->pipe_num > PIPE_BUF)
	{
		ft_printf("bash: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

void	ft_allocate_pipe_fds(t_pipe *pipe_data)
{
	pipe_data->pipe_fd = ft_calloc(sizeof(int *), (pipe_data->pipe_num + 1));
	pipe_data->i = 0;
	while (pipe_data->i < pipe_data->pipe_num)
	{
		pipe_data->pipe_fd[pipe_data->i] = malloc(sizeof(int) * 2);
		pipe(pipe_data->pipe_fd[pipe_data->i]);
		pipe_data->i++;
	}
}
