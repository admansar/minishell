
#include "minishell.h"

void ft_file_creation(t_input *list, t_redir *data)
{
	int		i;

	i = -1;
	while (list->redirect->type[++i])
	{
		if (!ft_strcmp(list->redirect->type[i], OUTPUT))
		{
			data->out_fd = open(list->redirect->file_name[i]
			, O_RDWR | O_CREAT | O_TRUNC , 0644);
			if (data->output <= i)
				data->output = i;
		}
		else if (!ft_strcmp(list->redirect->type[i], APPEND))
		{
			data->out_fd = open(list->redirect->file_name[i]
				, O_RDWR | O_CREAT | O_APPEND , 0666);
			if (data->output <= i)
				data->output = i;
		}
		else if (!ft_strcmp(list->redirect->type[i], INPUT))
		{
			if (access(list->redirect->file_name[i], F_OK | R_OK) == -1)
			{
				data->input_error = 1;
				printf("bash: %s: %s\n", list->redirect->file_name[i], strerror(errno));
				g_vars.g_exit_status = 1;
				break;
			}
			// data->input = i;
		}
	}
}

void	ft_get_input(t_input *list, t_redir *data)
{
	t_input	*tmp;
	int		i;

	tmp = list;
	data->herdoc_count = -1;
	data->input_count = -1;
	data->heredoc_exist = 0;
	data->input_exist = 0;
	i = -1;
	while (list->redirect->type[++i])
	{
		if (!strcmp(list->redirect->type[i], HERDOC))
		{
			data->herdoc_count = i;
			data->heredoc_exist = 1;
		}
		else if  (!ft_strcmp(list->redirect->type[i], INPUT))
		{
			data->input_count = i;
			data->input_exist = 1;
		}
	}
	if (data->herdoc_count > data->input_count && data->heredoc_exist)
	{
		data->in_fd = open(list->redirect->herdoc_file_name,
			O_RDONLY , 0644);
		unlink (list->redirect->herdoc_file_name);
	}
	else if (data->input_exist)
	{

		data->in_fd = open(list->redirect->file_name[data->input_count],
			O_RDONLY , 0644);
	}
}

void ft_redirections(t_input *list, t_redir *data, char ***env, char ***export)
{
	data->input_error = 0;
	data->output = 0;
	// data->input = 0;
	ft_file_creation(list, data);
	if (data->input_error)
		return;
	ft_get_input(list, data);
	int pid = fork();
	if (!pid)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
		if (list->cmd)
			ft_exec(list, env, export);
		//no idea what should in the exit status and I dont even know if it is important here
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

