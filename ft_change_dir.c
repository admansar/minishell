#include "minishell.h"

void    ft_change_dir(t_input *list, char ***env, char ***export)
{
    char    *old_pwd;
	char	*pwd;
	char	*leaks;
	char	*home_path;
    char    old_name[]="OLDPWD=";
    char    pwd_name[]="PWD=";
	char	path[10000];
	int		index_pwd;
	int		index_old_pwd;
	int		home_index;


    if (ft_strcount(list->arg) > 1)
	{
       ft_printf("bash: cd: too many arguments\n");
	   g_vars.g_exit_status = 1;
	   return;
	}
	else if (!ft_strcount(list->arg))
	{
		home_index = ft_in_env("HOME", *env);
		if (home_index > 0)
		{
			ft_get_var_value((*env)[home_index], "HOME", &home_path);
			chdir(home_path);
			if (!getcwd(path, sizeof(path)))
		{
			ft_printf("ERROR : path_name too long\n");
			g_vars.g_exit_status = 1;
			return;
		}
		index_pwd = ft_in_env("PWD", *env);
		index_old_pwd = ft_in_env("OLDPWD", *env);
		if (index_pwd > 0)
		{
			if(index_old_pwd > 0)
			{
				ft_get_var_value((*env)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(old_pwd, env, index_old_pwd);
				ft_update_value_env(pwd, env, index_pwd);
			}
			else
			{
				ft_get_var_value((*env)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(pwd, env, index_pwd);
				*env = ft_join_ptr_to_double_ptr(*env, old_pwd);
			}
			free(old_pwd);
			free(pwd);
		}
		in_env(NULL, *env, 1);
		index_pwd = ft_in_env("PWD", *export);
		index_old_pwd = ft_in_env("OLDPWD", *export);
		if (index_pwd > 0)
		{
			if(index_old_pwd > 0)
			{
				ft_get_var_value((*export)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(old_pwd, export, index_old_pwd);
				ft_update_value_env(pwd, export, index_pwd);
			}
			else
			{
				ft_get_var_value((*export)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(pwd, export, index_pwd);
				*export = ft_join_ptr_to_double_ptr(*export, old_pwd);
			}
			free(old_pwd);
			free(pwd);
		}
		}
		else
		{
			ft_printf("bash: cd: HOME not set\n");
			g_vars.g_exit_status = 1;
			return;
		}
	}
    else if (access(list->arg[0], F_OK | R_OK) == -1)
	{
        ft_printf("bash: cd: %s: No such file or directory\n", list->arg[0]);
		g_vars.g_exit_status = 1;
		return;
	}
    else
    {
        chdir(list->arg[0]);
		if (!getcwd(path, sizeof(path)))
		{
			ft_printf("ERROR : path_name too long\n");
			g_vars.g_exit_status = 1;
			return;
		}
		index_pwd = ft_in_env("PWD", *env);
		index_old_pwd = ft_in_env("OLDPWD", *env);
		if (index_pwd > 0)
		{
			if(index_old_pwd > 0)
			{
				ft_get_var_value((*env)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(old_pwd, env, index_old_pwd);
				ft_update_value_env(pwd, env, index_pwd);
			}
			else
			{
				ft_get_var_value((*env)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(pwd, env, index_pwd);
				*env = ft_join_ptr_to_double_ptr(*env, old_pwd);
			}
			free(old_pwd);
			free(pwd);
		}
		in_env(NULL, *env, 1);
		index_pwd = ft_in_env("PWD", *export);
		index_old_pwd = ft_in_env("OLDPWD", *export);
		if (index_pwd > 0)
		{
			if(index_old_pwd > 0)
			{
				ft_get_var_value((*export)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(old_pwd, export, index_old_pwd);
				ft_update_value_env(pwd, export, index_pwd);
			}
			else
			{
				ft_get_var_value((*export)[index_pwd], pwd_name, &old_pwd);
				leaks = ft_strjoin(old_name, old_pwd);
				free (old_pwd);
				old_pwd = leaks;
				pwd = ft_strjoin(pwd_name, path);
				ft_update_value_env(pwd, export, index_pwd);
				*export = ft_join_ptr_to_double_ptr(*export, old_pwd);
			}
			free(old_pwd);
			free(pwd);
		}
    }
	g_vars.g_exit_status = 0;
}
