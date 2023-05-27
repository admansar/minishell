
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
	int *arr = ft_calloc(sizeof(int) , (data->count + 1));
	i = -1;
	int j = 0;
	while (list->redirect->type[++i])
	{
		if (!list->redirect->file_name[i])
		{
			ft_printf("minishell: ambiguous redirect\n");
			// printf("file name : %s$\n", list->redirect->herdoc_file_name);
			data->error = 1;
			g_vars.g_exit_status = 1;
			break ;	
		}
		if (list->redirect->file_name[i] && list->redirect->file_name[i][0] == '\0')
		{
			ft_printf("minishell: No such file or directory\n");
			// printf("file name : %s$\n", list->redirect->file_name[i]);
			data->error = 1;
			g_vars.g_exit_status = 1;
			break ;
		}
		if (list->redirect->file_name[i] && list->redirect->file_name[i][0] == '\2')
		{
			ft_printf("minishell: ambiguous redirect\n");
			// printf("file name : %s$\n", list->redirect->file_name[i]);
			data->error = 1;
			g_vars.g_exit_status = 1;
			break ;
		}
		if (char_counter(list->redirect->file_name[i], '\2'))
		{
			disable (&list->redirect->file_name[i], '\2');
		}
		// if (list->redirect->file_name[i])
		// {
		// 	printf("file name : $%s$\n", list->redirect->file_name[i]);

		// }
		// pause(); 
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
			// else if(list->redirect->file_name[i] == NULL)
			// {
			// 	ft_printf("minishell: No such file or directory\n");
			// 	g_vars.g_exit_status = 1;
			// 	data->error = 1;
			// 	break;
			// }
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
	if(j > 0)
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
	if (len > 0)
		if (str[len] == c)
			len--;
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
	int len;

	len = ft_strlen(str) - 1;
	i = 0;
	while (str[i+1])
	{
		if (str[i] == c && str[i+1] == c && i + 1 != len)
			return (1);
			i++;
	}
	return (0);	
}
char *clean_from (char *c, char l)
{
	int i;
	int j;
	char *re;

	i = 0;
	j = 0;
	re = malloc (sizeof (char) * (ft_strlen (c) + 1));
	while (c && c[i])
	{
		if (c[i] != l)
			re[j++] = c[i++];
			else 
			i++;
	}
	re[j] = '\0';
	return (re);
}

void	ft_redirections(t_input *list, t_redir *data, char ***env,
		char ***export)
{
	int	pid;
	char *tmp;

	data->error = 0;
	data->in_fd = 0;
	data->out_fd = 0 ;
	int i;
	i = -1;
	while (list->redirect->file_name[++i])
	{
		if (((ft_strlen (list->redirect->file_name[i]) == 2) && list->redirect->file_name[i][0] == '\2'))
		{
			// exchange (&list->redirect->file_name[i], '\4', '4');
			// printf("file name : %s$\n", list->redirect->file_name[i]);
			ft_printf("minishell: ambiguous redirect\n");
			g_vars.g_exit_status = 1;
			return;
		}
		// else 
		// {
		// 	disable (&list->redirect->file_name[i], '\2');
		// }
		tmp = clean_from (list->redirect->file_name[i], '\2');
		if (ft_char_checker(list->redirect->file_name[i], '\4') >= 0)
		{
			exchange (&list->redirect->file_name[i], '\4', '4');
			// printf("file name : %s$\n", list->redirect->file_name[i]);
			ft_printf("minishell: ambiguous redirect\n");
			g_vars.g_exit_status = 1;
			free (tmp);
			return;
		}
		else if (char_counter(list->redirect->file_name[i], '\1') 
			&& (inside_of(tmp, '\1') 
			|| consecutive (tmp, '\1') 
			|| ft_strlen (tmp) == 1))
		{
			ft_printf("minishell: ambiguous redirect\n");
			g_vars.g_exit_status = 1;
			free (tmp);
			return;
		}
		else if (ft_char_checker(tmp , '\1') >= 0)
		{
			disable(&list->redirect->file_name[i], '\1');
			disable(&list->redirect->file_name[i], '\2');
		}
		free (tmp);
	}
	
	ft_file_creation(list, data);
	if (data->error)
		return ;
	ft_get_input(list, data);
	pid = fork();
	if (!pid)
	{
		if (data->count > 0)
		{
			dup2(data->out_fd, STDOUT_FILENO);
			close(data->out_fd);
		}
		if (data->herdoc_count >= 0 || data->input_count >= 0)
		{
			dup2(data->in_fd, STDIN_FILENO);
			if (data->herdoc_count >= 0)
				unlink(list->redirect->herdoc_file_name);
			close(data->in_fd);
		}
		if (list->cmd)
			ft_exec(list, env, export);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}
