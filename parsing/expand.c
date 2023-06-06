/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:13:15 by admansar          #+#    #+#             */
/*   Updated: 2023/06/06 13:43:51 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand(char ***str_pro_max, char **env)
{
	t_expand	*expand;

	expand = malloc(sizeof(t_expand));
	get_size_to_expand(&expand->str, str_pro_max, env);
	expand->i = 0;
	expand->j = 0;
	expand->start = 0;
	expand->end = 0;
	fill_str(expand, str_pro_max, env);
	expand->i = -1;
	while ((*str_pro_max)[++expand->i])
		if (char_counter((*str_pro_max)[expand->i], '$'))
			should_i_expand(expand, str_pro_max, env);
	free_double_array(expand->str);
	free(expand);
}

void	should_i_expand(t_expand *expand, char ***str_pro_max, char **env)
{
	(*expand).j = (*expand).i;
	expand_after_redirections(&(*expand), str_pro_max, env);
	if ((*expand).to_expand == 0)
		(*str_pro_max)[(*expand).i] = ft_str_join((*str_pro_max)[(*expand).i],
				"\a");
	if (surounded_by((*str_pro_max)[(*expand).i], '\"')
			&& expand->to_expand == 2)
		i_should_replace_them(&(*str_pro_max)[(*expand).i]);
	else if (!surounded_by((*str_pro_max)[(*expand).i], '\'')
			&& (*expand).to_expand == 1)
	{
		free((*str_pro_max)[(*expand).i]);
		(*str_pro_max)[(*expand).i] = ft_strdup((*expand).str[(*expand).i]);
	}
}

void	shlvl(char ***env, int c)
{
	int		i;
	int		h;
	char	*tmp;
	char	*tmp2;
	char	*shell_lvl;

	h = ft_strlen("SHLVL=");
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "SHLVL=", h))
		{
			tmp = take_copy((*env)[i], h, ft_strlen((*env)[i]));
			tmp2 = ft_itoa(ft_atoi(tmp) + c);
			free(tmp);
			free((*env)[i]);
			(*env)[i] = ft_strjoin("SHLVL=", tmp2);
			free(tmp2);
			return ;
		}
		i++;
	}
	shell_lvl = ft_strdup("SHLVL=1");
	ft_join_str_to_double_array(env, &shell_lvl);
	free (shell_lvl);
}

int	error_detected(void)
{
	ft_printf("bash: syntax error near unexpected token `|'\n");
	g_vars.g_exit_status = 2;
	return (0);
}

int	fast_check(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (error_detected());
	while (input[i])
		i++;
	i--;
	while (i > 0 && input[i] == ' ')
		i--;
	if (i >= 0)
	{
		if (input[i] == '|')
			return (error_detected());
	}
	else
		return (0);
	return (1);
}
