#include "../minishell.h"

void	ft_path_fixing(t_execution *data, char ***envi)
{
	data->tmp = take_copy((*envi)[data->inside], ft_simularity_len((*envi)[data->inside], '=')
		+ 1, ft_strlen((*envi)[data->inside]));
	data->found = ft_strlen (data->tmp) - 1;
	if (data->tmp[0] == ':')
	{
		data->tmp1 = ft_strjoin("->", data->tmp);
		if (data->tmp1 && data->tmp[data->found] == ':')
			data->tmp1 = ft_str_join(data->tmp1, "->");
		else if (data->tmp[data->found] == ':')
			data->tmp1 = ft_strjoin(data->tmp, "->");	
	}
	data->in_mid = found_in_middle(data->tmp);
	if (data->in_mid)
		data->tmp1 = ft_fix_path(data->tmp1, data->in_mid);
	free(data->tmp1);
	free (data->tmp);	
}

void	ft_current_dir_executables(t_input *list, t_execution *data, char ***envi)
{
	g_vars.pid[g_vars.index] = fork();
	if (g_vars.pid[g_vars.index] == 0)
	{
		data->arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
		execve(list->cmd, data->arg, *envi);
		perror("execve");
	}
	waitpid(g_vars.pid[g_vars.index++], &data->status, 0);
	if (WEXITSTATUS(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
	{
		data->status = WTERMSIG(data->status) + 128;
	}
	g_vars.g_exit_status = data->status;	
}

void	ft_cmd_with_path(t_input *list, t_execution *data, char ***envi)
{
	g_vars.pid[g_vars.index] = fork();
	if (g_vars.pid[g_vars.index] == 0)
	{
		data->env = ft_calloc(2, sizeof(char *));
		data->env[0] = take_copy(list->cmd, ft_strrchr(list->cmd, '/')
				- list->cmd, ft_strlen(list->cmd));
		list->arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
		execve(list->cmd, list->arg, *envi);
		perror("execve");
	}
	waitpid(g_vars.pid[g_vars.index++], &data->status, 0);
	if (WEXITSTATUS(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
	{
		data->status = WTERMSIG(data->status) + 128;
	}
	g_vars.g_exit_status = data->status;
}

void	ft_execute(t_input *list, t_execution *data, char ***envi)
{
		g_vars.pid[g_vars.index] = fork();
		if (g_vars.pid[g_vars.index] == 0)
		{
			list->arg = ft_join_double_ptr_to_ptr(data->acces[data->i], list->arg);
			execve(data->acces[data->i], list->arg, *envi);
			ft_printf("bash: command not found\n");
			exit(127);
		}
		waitpid(g_vars.pid[g_vars.index++], &data->status, 0);
		if (WEXITSTATUS(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
		{
			data->status = WTERMSIG(data->status) + 128;
		}
		g_vars.g_exit_status = data->status;
}	

void	ft_execute_cmd(t_input *list, t_execution *data, char ***envi)
{
	ft_join_path_and_cmd(list, data, envi);
	ft_check_access(data);
	if (data->found)
		ft_execute(list, data, envi);
	else
	{
		ft_printf("bash: %s: command not found\n", list->cmd);
		data->status = 127;
		g_vars.g_exit_status = data->status;
	}
	free_double_array(data->env);
	free_double_array(data->acces);
}