/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:17:33 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/18 20:25:18 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

// execution
void ft_execution(t_input *list, char ***env, char ***export)
{
	ft_pipe(list, env, export);
}

void ft_exec(t_input *list, char ***envi, char ***export)
{
	(void)list;
	int id1;
	int inside;
	char *tmp;
	char **env;
	char **acces;
	char **arg;
	int found;
	int i;

	inside = ft_in_env("PATH", *envi);
	if (!ft_strcmp(list->cmd, "export"))
		ft_export(envi, list, export);
	else if (!ft_strcmp(list->cmd, "unset"))
		ft_unset(envi, list, export);
	else if (!ft_strcmp(list->cmd, "env"))
		printer(*envi);
	else if (!ft_strcmp(list->cmd, "cd"))
		ft_change_dir(list, envi, export);
	else if(!ft_strcmp(list->cmd, "pwd"))
		ft_pwd(list, envi, export);
	else if(!ft_strcmp(list->cmd, "echo"))
		ft_echo(list);
	else
	{

		if (access(list->cmd, F_OK | X_OK) + 1 && !ft_strncmp(list->cmd, "./", 3))
		{
			id1 = fork();
			if (id1 == 0)
			{
				arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
				execve(list->cmd, arg, *envi);
				free(arg);
			}
			wait(NULL);
		}
		else if (char_counter(list->cmd, '/') && access(list->cmd, F_OK | X_OK) + 1)
		{
			id1 = fork();
			if (id1 == 0)
			{
				env = ft_calloc(2, sizeof(char *));
				env[0] = take_copy(list->cmd, ft_strrchr(list->cmd, '/') - list->cmd, ft_strlen(list->cmd));
				arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
				execve(list->cmd, arg, *envi);
				free_double_array(env);
				free(arg);
			}
			wait(NULL);
		}
		else if (inside + 1 && !char_counter(list->cmd, '/'))
		{
			tmp = take_copy((*envi)[inside], ft_simularity_len((*envi)[inside], '=') + 1, ft_strlen((*envi)[inside]));
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
					break;
				}
				i++;
			}
			if (found)
			{
				id1 = fork();
				if (id1 == 0)
				{
					arg = ft_join_double_ptr_to_ptr(acces[i], list->arg);
					execve(acces[i], arg, *envi);
					free(arg);
				}
				wait(NULL);
			}
			else
			{
				ft_printf("bash: %s: command not found\n", list->cmd);
			}
			free_double_array(env);
			free_double_array(acces);
		}
		else
		{
			ft_printf("bash: %s: command not found\n", list->cmd);
		}
	}
}

int ft_list_size(t_input *list)
{
	int i;

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


void ft_pipe(t_input *list, char ***envi, char ***export)
{
	int **pipe_fd;
	int *pid;
	int pipe_num;
	int i;
	t_input *tmp;

	if (!list->pipe)
	{
		if (list->redirect->position)
			ft_redirections(list, envi, export);
		else
			ft_exec(list, envi, export);
		return;
	}
	pipe_num = ft_list_size(list) - 1;
	pipe_fd = malloc (sizeof (int *) * (pipe_num));
	i = 0;
	while (i < pipe_num)
	{
		pipe_fd[i] = malloc (sizeof (int) * 2);
		i++;
	}
	pid = malloc (sizeof (int) * (pipe_num + 1));
	i = 0;
	tmp = list;
	while (i < pipe_num)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	i = 0;
	list = tmp;
	int j = 0;
	while (list)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror ("fork");
			while (i--)
			{
				kill (pid[i], SIGKILL);
				free (pipe_fd[i]);
			}
			free (pipe_fd);
			free (pid);
			return ;
//			exit (1);
		}
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				close (pipe_fd[i][0]);
				dup2 (pipe_fd[i][1], STDOUT_FILENO);
				close (pipe_fd[i][1]);
			}
			else if (i == pipe_num)
			{	
				close (pipe_fd[i-1][1]);
				dup2 (pipe_fd[i-1][0], STDIN_FILENO);
				close (pipe_fd[i-1][0]);
			}
			else
			{
				close (pipe_fd[i-1][1]);
				close (pipe_fd[i][0]);
				dup2 (pipe_fd[i-1][0],STDIN_FILENO);
				close (pipe_fd[i-1][0]);
				dup2(pipe_fd[i][1], STDOUT_FILENO);
				close (pipe_fd[i][1]);
			}
			j = 0;
			while (j < pipe_num)
			{
				close (pipe_fd[j][0]);
				close (pipe_fd[j][1]);
				j++;
			}
			ft_exec(list, envi, export);
			exit (1);
		}
		i++;
		list = list->next;
	}
	list = tmp;
	j = 0;
	while (j < pipe_num)
	{
		close (pipe_fd[j][0]);
		close (pipe_fd[j][1]);
		j++;
	}
	i = 0;
	while (i <= pipe_num)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	i = 0;
	while (i < pipe_num)
	{
		kill (pid[i], SIGKILL);
		free (pipe_fd[i]);
		i++;
	}
	kill (pid[i], SIGKILL);
	free (pipe_fd);
	free (pid);
}
