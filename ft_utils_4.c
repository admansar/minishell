#include "minishell.h"

void	ft_update_last_command(char ***env, t_input *list)
{
	int		index;
	char	*tmp_name;
	char	*new_val;

	new_val = NULL;
	index = ft_in_env("_", *env);
	if (index >= 0)
	{
		if (!list->cmd || list->pipe)
			new_val = ft_strdup("");
		else if (list->cmd)
			new_val = ft_strdup(list->cmd);
		ft_get_var_name((*env)[index], &tmp_name);
		tmp_name = ft_str_join(ft_str_join(tmp_name, "="), new_val);
		ft_update_value_env(tmp_name, env, index);
		free(new_val);
		free(tmp_name);
	}
}

void	ft_update_exit_status(char ***env)
{
	int		exist;
	char	*tmp_name;
	char	*itoi_arr;;

	exist = ft_in_env("?", *env);
	if (exist >= 0)
	{
		ft_get_var_name((*env)[exist], &tmp_name);
		itoi_arr = ft_itoa(g_vars.g_exit_status);
		tmp_name = ft_str_join(ft_str_join(tmp_name, "="), itoi_arr);
		ft_update_value_env(tmp_name, env, exist);
		free(itoi_arr);
		free(tmp_name);
	}
}