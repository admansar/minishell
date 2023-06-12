/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:23 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/12 20:01:26 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*tmp;

	ft_long_path_name(data);
	data->index_old_pwd = ft_in_env("OLDPWD", *ptr);
	if (data->index_old_pwd >= 0)
	{
		tmp = take_copy((*ptr)[data->index_pwd],
				ft_char_checker((*ptr)[data->index_pwd], '=') + 1,
				ft_strlen((*ptr)[data->index_pwd]));
		free((*ptr)[data->index_old_pwd]);
		(*ptr)[data->index_old_pwd] = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
	}
	free((*ptr)[data->index_pwd]);
	(*ptr)[data->index_pwd] = ft_strjoin("PWD=", data->path);
}

// handle the cd with no option or if we use the the $HOME variable
int	ft_home_dir(t_cd *data, char ***env, char ***export)
{
	(void)export;
	data->home_index = ft_in_env("HOME", *env);
	if (data->home_index >= 0)
	{
		ft_get_var_value((*env)[data->home_index], "HOME", &data->home_path);
		chdir(data->home_path);
		if (!ft_long_path_name(data))
			return (-1);
		data->index_pwd = ft_in_env("PWD", *env);
		if (data->index_pwd >= 0)
		{
			ft_update_pwd(data, export);
			ft_update_pwd(data, env);
			in_env(NULL, *env, 1);
		}
		free(data->home_path);
	}
	else
	{
		ft_printf("bash: cd: HOME not set\n");
		g_vars.g_exit_status = 1;
		return (-1);
	}
	g_vars.g_exit_status = 0;
	return (0);
}

void	ft_ch_dir(t_cd *data, char ***env, char ***export)
{
	(void)export;
	data->index_pwd = ft_in_env("PWD", *env);
	if (data->index_pwd >= 0)
	{
		ft_update_pwd(data, export);
		ft_update_pwd(data, env);
		in_env(NULL, *env, 1);
	}
	g_vars.g_exit_status = 0;
}

void	ft_change_directory(t_input *list, char ***env, char ***export)
{
	t_cd	data;

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
}
