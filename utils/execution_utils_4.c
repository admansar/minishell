/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:00 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/03 20:18:01 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_error(t_pipe *pipe_data)
{
	if (g_vars.pid[g_vars.index] == -1)
	{
		while (pipe_data->i--)
		{
			kill(g_vars.pid[pipe_data->i], SIGKILL);
			free(pipe_data->pipe_fd[pipe_data->i]);
		}
		perror("fork");
		return (1);
	}
	return (0);
}

void	ft_close(t_pipe *pipe_data)
{
	pipe_data->j = 0;
	while (pipe_data->j < pipe_data->pipe_num)
	{
		close(pipe_data->pipe_fd[pipe_data->j][0]);
		close(pipe_data->pipe_fd[pipe_data->j][1]);
		pipe_data->j++;
	}
}

void	ft_get_exit_status(t_pipe *pipe_data)
{
	pipe_data->i = 0;
	while (pipe_data->i <= pipe_data->pipe_num)
	{
		waitpid(g_vars.pid[pipe_data->i], &pipe_data->status, 0);
		if (WEXITSTATUS(pipe_data->status))
			pipe_data->status = WEXITSTATUS(pipe_data->status);
		else if (WIFSIGNALED(pipe_data->status))
		{
			pipe_data->status = WTERMSIG(pipe_data->status) + 128;
			if (pipe_data->status == 141)
				pipe_data->status = 0;
		}
		g_vars.g_exit_status = pipe_data->status;
		pipe_data->i++;
	}
}
