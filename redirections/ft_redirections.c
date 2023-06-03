#include "../minishell.h"

int	check_in_file_permissions(t_input *list, t_redir *data, int i)
{
	if (list->redirect->file_name[i] == NULL)
	{
		ft_error(data, AMBIGUOUS_ERR);
		return (0);
	}
	if (list->redirect->file_name[i][0] == '$')
	{
		ft_error(data, AMBIGUOUS_ERR);
		return (0);
	}
	data->error = 1;
	g_vars.g_exit_status = 1;
	ft_printf("bash: %s: %s\n", list->redirect->file_name[i],
			strerror(errno));
	return (0) ;
}

int	redirections_error(t_input *list, t_redir *data, t_files *f_data)
{
	if (!ft_strcmp(list->redirect->type[f_data->i], OUTPUT))
	{
		if (file_found(list, f_data)
			&& !ft_check_permissions(list, data, f_data, O_TRUNC))
			return (1);
		else
			ft_create_file(list, data, f_data, O_TRUNC);
	}
	else if (!ft_strcmp(list->redirect->type[f_data->i], APPEND))
	{
		if (file_found(list, f_data)
			&& !ft_check_permissions(list, data, f_data, O_APPEND))
			return (1);
		else
			ft_create_file(list, data, f_data, O_APPEND);
	}
	else if (!ft_strcmp(list->redirect->type[f_data->i], INPUT))
	{
		if (access(list->redirect->file_name[f_data->i], F_OK | R_OK) == -1)
			if (!check_in_file_permissions(list, data, f_data->i))
				return (1);
	}
	return (0);
}

void	ft_file_creation(t_input *list, t_redir *data)
{
	t_files	f_data;

	data->output = -1;
	data->count = 0;
	ft_get_all_fds(&f_data, list, data);
	while (list->redirect->type[++f_data.i])
	{
		if (ft_ambiguous(list, data, f_data.i))
			break;
		if (char_counter(list->redirect->file_name[f_data.i], '\2'))
			disable (&list->redirect->file_name[f_data.i], '\2');
		if (redirections_error(list, data, &f_data))
			break;
	}
	get_out_fd(&f_data, data);
}

void	ft_get_input(t_input *list, t_redir *data)
{
	t_input	*tmp;
	int		i;

	tmp = list;
	data->herdoc_count = -1;
	data->input_count = -1;
	i = -1;
	while (list->redirect->type[++i])
	{
		if (!strcmp(list->redirect->type[i], HERDOC))
			data->herdoc_count = i;
		else if (!ft_strcmp(list->redirect->type[i], INPUT))
			data->input_count = i;
	}
	if (data->herdoc_count > data->input_count)
	{
		data->in_fd = open(list->redirect->herdoc_file_name,
			O_RDONLY, 0644);
		unlink(list->redirect->herdoc_file_name);
		free(list->redirect->herdoc_file_name);
    }
	else if (data->herdoc_count < data->input_count)
		data->in_fd = open(list->redirect->file_name[data->input_count],
			O_RDONLY, 0644);
}

void	ft_redirections(t_input *list, t_redir *data, char ***env,
		char ***export)
{
	init_vars(data);
	if (ft_early_ambiguous_check(list, data))
		return ;
	ft_file_creation(list, data);
	if (data->error)
		return ;
	ft_get_input(list, data);
	data->pid = fork();
	if (!data->pid)
	{
		if (data->count > 0)
		{
			dup2(data->out_fd, STDOUT_FILENO);
			close(data->out_fd);
		}
		if (data->herdoc_count >= 0 || data->input_count >= 0)
		{
			dup2(data->in_fd, STDIN_FILENO);
			close(data->in_fd);
		}
		if (list->cmd)
			ft_exec(list, env, export);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}
