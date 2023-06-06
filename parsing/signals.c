/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:20:46 by admansar          #+#    #+#             */
/*   Updated: 2023/06/06 13:18:01 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint(int i)
{
	if (g_vars.here_doc)
		g_vars.g_exit_status = 1;
	else if (g_vars.pid[i] == 0)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_vars.g_exit_status = 0;
	}
	else
	{
		while (g_vars.pid[i] != 0)
		{
			kill (g_vars.pid[i], SIGINT);
			g_vars.pid[i] = 0;
			i++;
		}
		ft_bzero (g_vars.pid, PIPE_BUF);
		g_vars.index = 0;
		g_vars.g_exit_status = 130;
	}
}

void	sigquit(int i)
{
	if (!g_vars.pid[i])
		return ;
	while (g_vars.pid[i] != 0)
	{
		kill(g_vars.pid[i], SIGINT);
		g_vars.pid[i] = 0;
		i++;
	}
	ft_bzero(g_vars.pid, PIPE_BUF);
	g_vars.index = 0;
	ft_printf("Quit: 3\n");
}

void	signals(int signum)
{
	int	i;

	i = 0;
	if (signum == SIGINT)
		sigint(i);
	else if (signum == SIGQUIT)
		sigquit(i);
}
