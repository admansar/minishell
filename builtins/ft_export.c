#include "../minishell.h"

// adding my var to the env by allocating an extra space for it
void	ft_add_var_to_env(char ***env, char *variable)
{
	char	**new_env;
	int		i;
	int		j;
	int		n;
	int		len;

	len = ft_strcount(*env);
	new_env = (char **)ft_calloc(sizeof(char *), (len + 2));
	i = -1;
	n = 0;
	j = len - 2;
	while ((*env)[++i] && (i != j))
		new_env[i] = (*env)[i];
	new_env[i] = (*env)[i];
	n = ++i;
	new_env[n++] = ft_strdup(variable);
	new_env[n] = (*env)[i];
	free(*env);
	(*env) = new_env;
}

// create a char* var -----> "name=value"
char	*ft_create_var(char *name, char *value)
{
	char	*var;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(name) + ft_strlen(value);
	var = ft_calloc(sizeof(char), len + 1);
	i = -1;
	if (name)
		while (name[++i])
			var[i] = name[i];
	j = 0;
	if (value)
		while (i < len)
			var[i++] = value[j++];
	return (var);
}


int	ft_get_var(char *var, char **name, char **value)
{
	t_export	data;

	data.ret = ft_char_checker(var, '=');
	if (data.ret == -1)
	{
		data.len = ft_strlen(var);
		*name = take_copy(var, 0, data.len);
		*value = NULL;
		if (ft_simularity_len(var, '+') == data.len - 1)
			return (-13);
	}
	else
	{
		data.ret++;
		*name = (char *)ft_calloc(sizeof(char), data.ret + 1);
		data.i = -1;
		while (++data.i < data.ret)
			(*name)[data.i] = var[data.i];
		data.len = ft_strlen(var) - ft_strlen(*name);
		*value = (char *)ft_calloc(sizeof(char), data.len + 3);
		data.i = -1;
		while (++data.i < data.len)
			(*value)[data.i] = var[data.i + data.ret];
	}
	return (0);
}


void	ft_clean_up_vars(char ***export)
{
	int		i;
	int		ret;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while ((*export)[i])
	{
		ret = ft_char_checker((*export)[i], '+');
		if (ret >= 0)
		{
			tmp = take_copy((*export)[i], 0, ret - 1);
			tmp1 = take_copy((*export)[i], ret + 1, ft_strlen((*export)[i]));
			(*export)[i] = ft_str_join(tmp, tmp1);
		}
		i++;
	}
}

char	**ft_check_env_var(char **valid_export_vars)
{
	t_export	data;

	data.len = ft_strcount(valid_export_vars) + 1;
	data.arr = (int *)ft_calloc(sizeof(int), data.len);
	data.i = -1;
	data.count = 0;
	while (valid_export_vars[++data.i])
	{
		if (ft_char_checker(valid_export_vars[data.i], '=') >= 0)
		{
			data.arr[data.i] = 1;
			data.count++;
		}
	}
	data.env_vars = (char **)ft_calloc(sizeof(char *), data.count + 1);
	data.i = -1;
	data.j = 0;
	while (++data.i < data.len)
	{
		if (data.arr[data.i])
			data.env_vars[data.j++] = ft_strdup(valid_export_vars[data.i]);
	}
	free(data.arr);
	return (data.env_vars);
}

void	ft_update_value_env(char *arr, char ***export, int pos)
{
	free((*export)[pos]);
	(*export)[pos] = ft_strdup(arr);
}

void	ft_export(char ***env, t_input *list, char ***export)
{
	char	**valid_export_vars;
	char	**valid_env_vars;
	int		exist;
	char	*tmp_name;
	char	*tmp_value;
	int		var_nbr;
	int		j;
	int		i;
	int		ret;
	if (!list->arg[0])
	{
		ft_export_printer(*export);
		return ;
	}
	var_nbr = ft_strcount(list->arg);
	valid_export_vars = ft_calloc(sizeof(char *), var_nbr + 1);
	i = 0;
	j = 0;
	while (list->arg[i])
	{
		ret = ft_get_var(list->arg[i], &tmp_name, &tmp_value);
		if (ft_export_name_checker(tmp_name) == -1 || ret == -13)
		{
			ft_printf("bash: export: `%s': not a valid identifier\n",
					list->arg[i]);
			g_vars.g_exit_status = 1;
		}
		else
		{
			valid_export_vars[j] = ft_strdup(list->arg[i]);
			ft_clean_up_name(&(valid_export_vars[j]));
			j++;
			g_vars.g_exit_status = 0;
		}
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	valid_env_vars = ft_check_env_var(valid_export_vars);
	i = 0;
	while (valid_export_vars[i])
	{
		ft_get_var_name(valid_export_vars[i], &tmp_name);
		ft_get_var_value(valid_export_vars[i], tmp_name, &tmp_value);
		exist = ft_in_env(tmp_name, *export);
		if (exist == -1)
			*export = ft_join_ptr_to_double_ptr(*export, valid_export_vars[i]);
		else if (tmp_value)
			ft_update_value_env(valid_export_vars[i], export, exist);
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	i = 0;
	while (valid_env_vars[i])
	{
		ft_get_var_name(valid_env_vars[i], &tmp_name);
		ft_get_var_value(valid_env_vars[i], tmp_name, &tmp_value);
		exist = ft_in_env(tmp_name, *env);
		if (exist == -1)
			*env = ft_join_ptr_to_double_ptr(*env, valid_env_vars[i]);
		else if (tmp_value)
			ft_update_value_env(valid_env_vars[i], env, exist);
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	in_env(NULL, *env, 1);
	free_double_array(valid_env_vars);
	free_double_array(valid_export_vars);
}
