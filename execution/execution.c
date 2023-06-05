/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:17:33 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/05 16:54:56 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	basic_execution(t_input *list, char ***envi)
{
	t_execution	data;

	data.tmp1 = NULL;
	data.inside = ft_in_env("PATH", *envi);
	if (data.inside + 1)
		ft_path_fixing(&data, envi);
	if (access(list->cmd, F_OK | X_OK) + 1 && !ft_strncmp(list->cmd, "./", 3))
		ft_current_dir_executables(list, &data, envi);
	else if (!ft_strcmp(list->cmd, "/"))
	{
		ft_printf("bash: /: is a directory\n");
		g_vars.g_exit_status = 126;
	}
	else if (char_counter(list->cmd, '/') && access(list->cmd, F_OK | X_OK) + 1)
		ft_cmd_with_path(list, &data, envi);
	else if (data.inside + 1 && !char_counter(list->cmd, '/'))
		ft_execute_cmd(list, &data, envi);
	else
	{
		ft_printf("bash: %s\n", strerror(errno));
		data.status = 127;
		g_vars.g_exit_status = data.status;
	}
}

void	ft_exec(t_input *list, char ***envi, char ***export)
{
	if (!ft_strcmp(list->cmd, "export"))
		ft_export(envi, list, export);
	else if (!ft_strcmp(list->cmd, "exit"))
		ft_exit(list);
	else if (!ft_strcmp(list->cmd, "unset"))
		ft_unset(envi, list, export);
	else if (!ft_strcmp(list->cmd, "env"))
	{
		ft_update_last_command(envi, list);
		printer(*envi);
	}
	else if (!ft_strcmp(list->cmd, "cd"))
		ft_change_directory(list, envi, export);
	else if (!ft_strcmp(list->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(list->cmd, "echo"))
		ft_echo(list);
	else
		basic_execution(list, envi);
}

void	ft_n_pipe(t_input *list, t_pipe *pipe_data, t_redir *data)
{
	pipe_data->i = 0;
	while (list)
	{
		g_vars.pid[g_vars.index] = fork();
		if (fork_error(pipe_data))
			return ;
		if (g_vars.pid[g_vars.index] == 0)
		{
			if (pipe_data->i < pipe_data->pipe_num)
				dup2(pipe_data->pipe_fd[pipe_data->i][1], STDOUT_FILENO);
			if (pipe_data->i > 0)
				dup2(pipe_data->pipe_fd[pipe_data->i - 1][0], STDIN_FILENO);
			ft_close(pipe_data);
			if (list->redirect->position)
				ft_redirections(list, data, pipe_data->env, pipe_data->export);
			else
				ft_exec(list, pipe_data->env, pipe_data->export);
			exit(g_vars.g_exit_status);
		}
		pipe_data->i++;
		g_vars.index++;
		list = list->next;
	}
}

void	ft_pipe(t_input *list, t_redir *data, char ***envi, char ***export)
{
	t_pipe	pipe_data;

	pipe_data.env = envi;
	pipe_data.export = export;
	list = ft_skip_same_cmd(list);
	pipe_data.pipe_num = ft_list_size(list) - 1;
	if (ft_check_pipe_errors(list, &pipe_data, envi, export))
		return ;
	ft_allocate_pipe_fds(&pipe_data);
	ft_n_pipe(list, &pipe_data, data);
	ft_close(&pipe_data);
	ft_get_exit_status(&pipe_data);
	pipe_data.i = 0;
	while (pipe_data.i < pipe_data.pipe_num)
	{
		free(pipe_data.pipe_fd[pipe_data.i++]);
	}
	ft_bzero(g_vars.pid, pipe_data.i + 1);
	g_vars.index = 0;
	free(pipe_data.pipe_fd);
}

void	ft_execution(t_input *list, char ***env, char ***export)
{
	t_redir	data;

	ft_execute_here_docs(list, &data, env, export);
	if (!list->pipe)
	{
		if (list->redirect->position)
			ft_redirections(list, &data, env, export);
		else
			ft_exec(list, env, export);
	}
	else
		ft_pipe(list, &data, env, export);
}
