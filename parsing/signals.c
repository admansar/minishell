/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:20:46 by admansar          #+#    #+#             */
/*   Updated: 2023/06/14 11:33:51 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint(void)
{
	if (g_vars.here_doc)
	{
		ft_printf("\n");
		rl_on_new_line();
		g_vars.killed_heardoc = 1;
		g_vars.g_exit_status = 1;
	}
	else if (!g_vars.pid[0])
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_vars.g_exit_status = 1;
		g_vars.index = 0;
		g_vars.pid[0] = 0;
	}
	ft_update_exit_status(&g_vars.env);
}

void	signals(int signum)
{
	if (signum == SIGINT)
		sigint();
}
