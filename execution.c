/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:17:33 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/26 21:53:59 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// execution
void	ft_execution(t_input *list, char ***env, char ***export)
{
	t_redir	data;
	t_input	*tmp;

	tmp = list;
	ft_execute_here_docs(list, &data, env, export);
	if (!list->pipe)
	{
		if (list->redirect->position)
			ft_redirections(list, &data, env, export);
		else
			ft_exec(list, env, export);
		return ;
	}
	else
		ft_pipe(list, &data, env, export);
	tmp = list;
	while (tmp)
	{
		if (tmp->redirect->position)
			free(tmp->redirect->herdoc_file_name);
		tmp = tmp->next;
	}
}

void	basic_execution(t_input *list, char ***envi)
{
	int		inside;
	char	*tmp;
	char	**env;
	char	**acces;
	char	**arg;
	int		found;
	int		i;
	int		status;

	inside = ft_in_env("PATH", *envi);
	if (access(list->cmd, F_OK | X_OK) + 1 && !ft_strncmp(list->cmd, "./", 3))
	{
		g_vars.pid[g_vars.index] = fork();
		if (g_vars.pid[g_vars.index] == 0)
		{
			arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
			execve(list->cmd, arg, *envi);
			perror("execve");
		}
		waitpid(g_vars.pid[g_vars.index++], &status, 0);
		if (WEXITSTATUS(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status) + 128;
		}
		g_vars.g_exit_status = status;
	}
	else if (!ft_strcmp(list->cmd, "/"))
	{
		ft_printf("bash: /: is a directory\n");
		g_vars.g_exit_status = 126;
	}
	else if (char_counter(list->cmd, '/') && access(list->cmd, F_OK | X_OK) + 1)
	{
		g_vars.pid[g_vars.index] = fork();
		if (g_vars.pid[g_vars.index] == 0)
		{
			env = ft_calloc(2, sizeof(char *));
			env[0] = take_copy(list->cmd, ft_strrchr(list->cmd, '/')
					- list->cmd, ft_strlen(list->cmd));
			list->arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
			execve(list->cmd, list->arg, *envi);
			perror("execve");
		}
		waitpid(g_vars.pid[g_vars.index++], &status, 0);
		if (WEXITSTATUS(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status) + 128;
		}
		g_vars.g_exit_status = status;
	}
	else if (inside + 1 && !char_counter(list->cmd, '/'))
	{
		tmp = take_copy((*envi)[inside], ft_simularity_len((*envi)[inside], '=')
				+ 1, ft_strlen((*envi)[inside]));
		env = ft_split(tmp, ':');
		free(tmp);
		acces = ft_calloc(sizeof(char *), ft_strcount(env) + 1);
		i = 0;
		while (env[i])
		{
			tmp = ft_strjoin("/", list->cmd);
			acces[i] = ft_strjoin(env[i], tmp);
			free(tmp);
			i++;
		}
		i = 0;
		found = 0;
		while (acces[i])
		{
			if (access(acces[i], F_OK | X_OK) + 1)
			{
				found = 1;
				break ;
			}
			i++;
		}
		if (found)
		{
			g_vars.pid[g_vars.index] = fork();
			if (g_vars.pid[g_vars.index] == 0)
			{
				list->arg = ft_join_double_ptr_to_ptr(acces[i], list->arg);
				execve(acces[i], list->arg, *envi);
				ft_printf("bash: command not found\n");
				exit(127);
			}
			waitpid(g_vars.pid[g_vars.index++], &status, 0);
			if (WEXITSTATUS(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				status = WTERMSIG(status) + 128;
			}
			g_vars.g_exit_status = status;
		}
		else
		{
			ft_printf("bash: %s: command not found\n", list->cmd);
			status = 127;
			g_vars.g_exit_status = status;
		}
		free_double_array(env);
		free_double_array(acces);
	}
	else
	{
		ft_printf("bash: %s\n", strerror(errno));
		status = 127;
		g_vars.g_exit_status = status;
	}
}

int	have_just_digits(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-')
		i++;
	while (c[i])
	{
		if (ft_isdigit(c[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_input *list)
{
	if (list->arg[0])
	{
		if (have_just_digits(list->arg[0]) && !list->arg[1])
		{
			exit(ft_atoi(list->arg[0]));
		}
		else if (!have_just_digits(list->arg[0]))
		{
			ft_printf("bash: exit: %s: numeric argument required\n",
					list->arg[0]);
			exit(255);
		}
		else if (list->arg[0] && list->arg[1])
		{
			ft_printf("bash: exit: too many arguments\n");
			g_vars.g_exit_status = 1;
			return ;
		}
	}
	else
	{
		exit(g_vars.g_exit_status);
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
		printer(*envi);
	else if (!ft_strcmp(list->cmd, "cd"))
		ft_change_directory(list, envi, export);
	else if (!ft_strcmp(list->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(list->cmd, "echo"))
		ft_echo(list);
	else
		basic_execution(list, envi);
}

int	ft_list_size(t_input *list)
{
	int	i;

	i = 0;
	if (!list)
		return (i);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	ft_pipe(t_input *list, t_redir *data, char ***envi, char ***export)
{
	int		**pipe_fd;
	int		pipe_num;
	int		i;
	int		j;
	int		status;
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
	list = tmp;
	pipe_num = ft_list_size(list) - 1;
	if (pipe_num == 0)
	{
		ft_exec(list, envi, export);
		return ;
	}
	if (pipe_num > PIPE_BUF)
	{
		ft_printf("bash: %s\n", strerror(errno));
		return ;
	}
	pipe_fd = ft_calloc(sizeof(int *), (pipe_num + 1));
	i = 0;
	while (i < pipe_num)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		pipe(pipe_fd[i]);
		i++;
	}
	i = 0;
	while (list)
	{
		g_vars.pid[g_vars.index] = fork();
		if (g_vars.pid[g_vars.index] == -1)
		{
			while (i--)
			{
				kill(g_vars.pid[i], SIGKILL);
				free(pipe_fd[i]);
			}
			perror("fork");
			return ;
		}
		if (g_vars.pid[g_vars.index] == 0)
		{
			if (i < pipe_num)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			j = 0;
			while (j < pipe_num)
			{
				close(pipe_fd[j][0]);
				close(pipe_fd[j][1]);
				j++;
			}
			if (list->redirect->position)
				ft_redirections(list, data, envi, export);
			else
				ft_exec(list, envi, export);
			exit(g_vars.g_exit_status);
		}
		i++;
		g_vars.index++;
		list = list->next;
	}
	j = 0;
	while (j < pipe_num)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		j++;
	}
	i = 0;
	while (i <= pipe_num)
	{
		waitpid(g_vars.pid[i], &status, 0);
		if (WEXITSTATUS(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status) + 128;
			if (status == 141)
				status = 0;
		}
		g_vars.g_exit_status = status;
		i++;
	}
	i = 0;
	while (i < pipe_num)
	{
		free(pipe_fd[i++]);
	}
	ft_bzero(g_vars.pid, i + 1);
	g_vars.index = 0;
	free(pipe_fd);
}
