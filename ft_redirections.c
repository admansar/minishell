
#include "minishell.h"

void	ft_file_creation(t_input *list, t_redir *data)
{
	int	i;
	int	ret;

	data->output = -1;
	data->count = 0;
	ret = 0;
	i = -1;
	while (list->redirect->type[++i])
	{
		if (!strcmp(list->redirect->type[i], OUTPUT))
			data->count++;
		else if (!ft_strcmp(list->redirect->type[i], APPEND))
			data->count++;
	}
	int *arr = malloc(sizeof(int) * data->count);
	i = -1;
	int j = 0;
	while (list->redirect->type[++i])
	{
		if (list->redirect->file_name == '\0')
		{
			ft_printf("minishell: No such file or directory\n");
			// printf("file name : %s$\n", list->redirect->herdoc_file_name);
			data->error = 1;
			g_vars.g_exit_status = 0;
			break ;
		}
		if (!ft_strcmp(list->redirect->type[i], OUTPUT))
		{
			if (!access(list->redirect->file_name[i], F_OK))
			{
				ret = access(list->redirect->file_name[i], R_OK | W_OK);
				if (!ret)
				{
					arr[j++] = open(list->redirect->file_name[i],
							O_RDWR | O_TRUNC, 0644);
					if (data->output <= i)
						data->output = i;
				}
				else if (ret == -1)
				{
					ft_printf("minishell: %s: %s\n", list->redirect->file_name[i],
							strerror(errno));
					data->error = 1;
					g_vars.g_exit_status = 1;
					break ;
				}
			}
			else if(list->redirect->file_name[i] == NULL)
			{
				ft_printf("minishell: No such file or directory\n");
				g_vars.g_exit_status = 1;
				data->error = 1;
				break;
			}
			else
			{
				arr[j++] = open(list->redirect->file_name[i],
						O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (data->output <= i)
					data->output = i;
			}
		}
		else if (!ft_strcmp(list->redirect->type[i], APPEND))
		{
			if (!access(list->redirect->file_name[i], F_OK))
			{
				ret = access(list->redirect->file_name[i], R_OK | W_OK);
				if (!ret)
				{
					arr[j++] = open(list->redirect->file_name[i],
							O_RDWR | O_APPEND, 0666);
					if (data->output <= i)
						data->output = i;
				}
				else if (ret == -1)
				{
					ft_printf("minishell: %s: %s\n", list->redirect->file_name[i],
							strerror(errno));
					data->error = 1;
					g_vars.g_exit_status = 1;
					break ;
				}
			}
			else
			{
				arr[j++] = open(list->redirect->file_name[i],
						O_RDWR | O_CREAT | O_APPEND, 0666);
				if (data->output <= i)
					data->output = i;
			}
		}
		else if (!ft_strcmp(list->redirect->type[i], INPUT))
		{
			if (access(list->redirect->file_name[i], F_OK | R_OK) == -1)
			{
				data->error = 1;
				if (list->redirect->file_name[i] == NULL)
				{
					ft_printf("minishell: ambiguous redirect\n");
					g_vars.g_exit_status = 1;
					data->error = 1;
					break;
				}
				printf("bash: %s: %s\n", list->redirect->file_name[i],
						strerror(errno));
				g_vars.g_exit_status = 1;
				break ;
			}
		}
	}
	data->out_fd = arr[j - 1];
	j = 0;
	while (j < data->count - 1)
		close(arr[j++]);
	free(arr);
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
			// unlink(list->redirect->herdoc_file_name);
    }
	else if (data->herdoc_count < data->input_count)
		data->in_fd = open(list->redirect->file_name[data->input_count],
			O_RDONLY, 0644);
}

int inside_of(char *str, char c)
{
	int len;
	int i;

	i = 1;
	len = ft_strlen (str) - 1;
	while (i < len && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	consecutive(char *str, char c)
{
	int i;

	i = 0;
	while (str[i+1])
	{
		if (str[i] == c && str[i+1] == c)
			return (1);
			i++;
	}
	return (0);	
}

void	ft_redirections(t_input *list, t_redir *data, char ***env,
		char ***export)
{
	int	pid;

	data->error = 0;
	data->in_fd = 0;
	data->out_fd = 0 ;
	int i;
	i = -1;
	while (list->redirect->file_name[++i])
	{
		if (ft_char_checker(list->redirect->file_name[i], '\4') >= 0)
		{
			exchange (&list->redirect->file_name[i], '\4', '4');
			// printf("file name : %s$\n", list->redirect->file_name[i]);
			ft_printf("minishell: ambiguous redirect\n");
			g_vars.g_exit_status = 1;
			return;
		}
		else if (char_counter(list->redirect->file_name[i], '\1') && (inside_of(list->redirect->file_name[i], '\1') || consecutive (list->redirect->file_name[i], '\1') || ft_strlen (list->redirect->file_name[i]) == 1))
		{
			ft_printf("minishell: ambiguous redirect\n");
			g_vars.g_exit_status = 1;
			return;
		}
	}
	
	ft_file_creation(list, data);
	if (data->error)
		return ;
	ft_get_input(list, data);
	pid = fork();
	if (!pid)
	{
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
		dup2(data->in_fd, STDIN_FILENO);
		if (data->herdoc_count >= 0)
			unlink(list->redirect->herdoc_file_name);
		close(data->in_fd);
		if (list->cmd)
			ft_exec(list, env, export);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}
