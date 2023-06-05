/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:09:12 by admansar          #+#    #+#             */
/*   Updated: 2023/06/05 12:43:21 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char ***env, char ***export)
{
	char	*input;
	char	*copy;

	if (!g_vars.g_exit_status)
		input = readline("😄\033[0;32mbash-4.2\033[34m$▶️  \033[0m");
	else
		input = readline("😡\033[31mbash-4.2\033[34m$❌ \033[0m");
	if (input == NULL)
	{
		// ft_printf ("exit\n");
		free(input);
		exit(g_vars.g_exit_status);
	}
	copy = ft_strdup(input);
	parse_phil_list_and_excute(&copy, env, export);
	free(copy);
	add_history(input);
	if (input && input[0] == 0)
		g_vars.g_exit_status = 0;
	free(input);
	ft_bzero(g_vars.pid, PIPE_BUF);
	g_vars.index = 0;
}

int	main(int ac, char **av, char **envi)
{
	char	**env;
	char	**export;

	(void)ac;
	(void)av;
	env = fill(envi);
	env = ft_join_ptr_to_double_ptr(env, "?=0");
	shlvl(&env, 1);
	in_env(NULL, env, 1);
	export = fill(env);
	g_vars.g_exit_status = 0;
	g_vars.index = 0;
	signal (SIGINT, signals);
	signal (SIGQUIT, signals);
	while (1)
		minishell(&env, &export);
	shlvl(&env, -1);
	in_env(NULL, env, 1);
	free_double_array(env);
	free_double_array(export);
	exit(0);
}
