/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:09:12 by admansar          #+#    #+#             */
/*   Updated: 2023/06/14 11:33:35 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char ***env, char ***export)
{
	char	*input;
	char	*copy;

	input = readline("\033[0;36mminishell-4.2$ \033[0;32m➜ \033[0m");
	if (input == NULL)
	{
		ft_printf ("exit\n");
		free(input);
		exit(g_vars.g_exit_status);
	}
	copy = ft_strdup(input);
	exchange(&copy, '\t', ' ');
	g_vars.killed_heardoc = 0;
	parse_phil_list_and_excute(&copy, env, export);
	free(copy);
	add_history(input);
	if (input && input[0] == 0)
		g_vars.g_exit_status = 0;
	free(input);
	ft_bzero(g_vars.pid, PIPE_BUF);
	g_vars.index = 0;
	g_vars.here_doc = 0;
	signal(SIGINT, signals);
}

int	main(int ac, char **av, char **envi)
{
	char	**export;

	(void)ac;
	(void)av;
	g_vars.env = fill(envi);
	g_vars.env = ft_join_ptr_to_double_ptr(g_vars.env, "?=0");
	shlvl(&g_vars.env, 1);
	in_env(NULL, g_vars.env, 1);
	export = fill(g_vars.env);
	export = ft_remove(export, ft_in_env("_", g_vars.env));
	g_vars.g_exit_status = 0;
	g_vars.index = 0;
	signal(SIGINT, signals);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		minishell(&g_vars.env, &export);
	shlvl(&g_vars.env, -1);
	in_env(NULL, g_vars.env, 1);
	free_double_array(g_vars.env);
	free_double_array(export);
	exit(0);
}
