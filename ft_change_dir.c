#include "minishell.h"

// error if the the path name is too long
int	ft_long_path_name(t_cd *data)
{
	if (!getcwd(data->path, sizeof(data->path)))
	{
		ft_printf("ERROR : path_name too long\n");
		g_vars.g_exit_status = 1;
		return (0);
	}
	return (1);
}

// update the value of $PWD and $OLDPWD in the given ptr
void	ft_update_pwd(t_cd *data, char ***ptr)
{
	if (data->index_old_pwd > 0)
	{
		ft_get_var_value((*ptr)[data->index_pwd],
			data->pwd_name, &data->old_pwd);
		data->joined = ft_strjoin(data->old_name, data->old_pwd);
		free(data->old_pwd);
		data->old_pwd = data->joined;
		data->pwd = ft_strjoin(data->pwd_name, data->path);
		ft_update_value_env(data->old_pwd, ptr, data->index_old_pwd);
		ft_update_value_env(data->pwd, ptr, data->index_pwd);
	}
	else
	{
		ft_get_var_value((*ptr)[data->index_pwd],
			data->pwd_name, &data->old_pwd);
		data->joined = ft_strjoin(data->old_name, data->old_pwd);
		free(data->old_pwd);
		data->old_pwd = data->joined;
		data->pwd = ft_strjoin(data->pwd_name, data->path);
		ft_update_value_env(data->pwd, ptr, data->index_pwd);
		*ptr = ft_join_ptr_to_double_ptr(*ptr, data->old_pwd);
	}
	free(data->old_pwd);
	free(data->pwd);
}

// handle the cd with no option or if we use the the $HOME variable
int	ft_home_dir(t_cd *data, char ***env, char ***export)
{
	data->home_index = ft_in_env("HOME", *env);
	if (data->home_index > 0)
	{
		ft_get_var_value((*env)[data->home_index], "HOME", &data->home_path);
		chdir(data->home_path);
		if (!ft_long_path_name(data))
			return (-1);
		data->index_pwd = ft_in_env("PWD", *env);
		data->index_old_pwd = ft_in_env("OLDPWD", *env);
		if (data->index_pwd > 0)
			ft_update_pwd(data, env);
		in_env(NULL, *env, 1);
		data->index_pwd = ft_in_env("PWD", *export);
		data->index_old_pwd = ft_in_env("OLDPWD", *export);
		if (data->index_pwd > 0)
			ft_update_pwd(data, export);
	}
	else
	{
		ft_printf("bash: cd: HOME not set\n");
		g_vars.g_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	ft_ch_dir(t_cd *data, char ***env, char ***export)
{
	data->index_pwd = ft_in_env("PWD", *env);
	data->index_old_pwd = ft_in_env("OLDPWD", *env);
	if (data->index_pwd > 0)
	{
		ft_update_pwd(data, env);
	}
	in_env(NULL, *env, 1);
	data->index_pwd = ft_in_env("PWD", *export);
	data->index_old_pwd = ft_in_env("OLDPWD", *export);
	if (data->index_pwd > 0)
		ft_update_pwd(data, export);
}

void	ft_change_directory(t_input *list, char ***env, char ***export)
{
	t_cd	data;

	ft_strlcpy(data.old_name, "OLDPWD=", 8);
	ft_strlcpy(data.pwd_name, "PWD=", 5);
	if (!ft_strcount(list->arg))
	{
		if (ft_home_dir(&data, env, export) == -1)
			return ;
	}
	else if (access(list->arg[0], F_OK | R_OK) == -1)
	{
		ft_printf("bash: cd: %s: No such file or directory\n", list->arg[0]);
		g_vars.g_exit_status = 1;
		return ;
	}
	else
	{
		chdir(list->arg[0]);
		if (!ft_long_path_name(&data))
			return ;
		ft_ch_dir(&data, env, export);
	}
	g_vars.g_exit_status = 0;
}
