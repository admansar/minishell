/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:45 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/12 20:15:29 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_get_operators_pos(t_input *list, char *str, int *count)
{
	int	*pos;
	int	i;
	int	j;

	*count = 0;
	j = 0;
	i = -1;
	while (list->redirect->type[++i])
		if (!ft_strcmp(list->redirect->type[i], str))
			(*count)++;
	if (*count == 0)
		return (NULL);
	pos = ft_calloc(sizeof(int), *count);
	i = -1;
	while (list->redirect->type[++i])
		if (!ft_strcmp(list->redirect->type[i], str))
			pos[j++] = i;
	return (pos);
}

void	ft_write_in_file(t_input *list, t_redir *data, char **env)
{
	g_vars.g_exit_status = 0;
	data->in_fd = open(list->redirect->herdoc_file_name,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->expand)
		array_expander(&data->input, env);
	ft_putstr_fd(data->input, data->in_fd);
	write(data->in_fd, "\n", 1);
	free(data->input);
}

// launch here-doc as many times as it appear in the input
void	ft_here_doc(t_input *list, int *pos, t_redir *data, t_rand_str *d)
{
	signal(SIGINT, SIG_IGN);
	g_vars.here_doc = fork();
	if (!g_vars.here_doc)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (++d->i < data->herdoc_count)
		{
			ft_check_expand(list, data, pos, d->i);
			while (1)
			{
				data->input = readline("> ");
				if (!data->input)
					break ;
				if (!ft_strcmp(data->input
						, list->redirect->file_name[pos[d->i]])
					&& ft_leave_current_heredoc(data, d->i))
					break ;
				else if (d->i == data->herdoc_count - 1)
					ft_write_in_file(list, data, (*data->env));
			}
		}
		exit (0);
	}
	wait (NULL);
}

void	ft_execute_here_docs(t_input *list, t_redir *data, char ***env,
		char ***export)
{
	t_rand_str	d;

	data->env = env;
	data->export = export;
	data->herdoc_count = 0;
	while (list)
	{
		if (list->redirect->position)
		{
			data->pos_herdoc = ft_get_operators_pos(list, HERDOC,
					&(data->herdoc_count));
			if (data->herdoc_count)
			{
				ft_get_rand_str(&d, data, list);
				d.i = -1;
				data->expand = 1;
				ft_here_doc(list, data->pos_herdoc, data, &d);
			}
			free(data->pos_herdoc);
		}
		list = list->next;
	}
}
