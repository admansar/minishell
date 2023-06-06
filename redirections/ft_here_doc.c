/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:45 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 01:08:09 by jlaazouz         ###   ########.fr       */
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

// void heredoc_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		// rl_replace_line("", 1);
// 		// rl_on_new_line();
// 		// rl_redisplay();
// 		exit (1);
// 	}
// }


// launch here-doc as many times as it appear in the input
void	ft_here_doc(t_input *list, int *pos, t_redir *data, t_rand_str *d)
{
	d->i = -1;
	data->expand = 1;
	g_vars.here_doc = fork();
	if (g_vars.here_doc == 0)
	{
		signal (SIGINT, SIG_DFL);
		while (++d->i < data->herdoc_count)
		{
			ft_check_expand(list, data, pos, d->i);
			while (1)
			{
				data->input = readline("> ");
				if (!data->input)
					break ;
				if (!ft_strcmp(data->input, list->redirect->file_name[pos[d->i]]))
				{
					ft_leave_current_heredoc(data, d->i);
					break ;
				}
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
	t_input		*tmp;
	t_rand_str	d;

	tmp = list;
	data->env = env;
	data->export = export;
	data->herdoc_count = 0;
	while (tmp)
	{
		if (tmp->redirect->position)
		{
			data->pos_herdoc = ft_get_operators_pos(tmp, HERDOC,
					&(data->herdoc_count));
			if (data->herdoc_count)
			{
				ft_get_rand_str(&d, data, list);
				// g_vars.pid[g_vars.index]= fork();
				// if (!g_vars.pid[g_vars.index])
				// {
					ft_here_doc(tmp, data->pos_herdoc, data, &d);
			}
			free(data->pos_herdoc);
		}
		tmp = tmp->next;
	}
}
