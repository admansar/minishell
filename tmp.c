void	ft_add_to_env(t_export *data, char ***env)
{
	int	i;

	i = 0;
	while (data->valid_env_vars[i])
	{
		ft_get_var_name(data->valid_env_vars[i], &data->tmp_name);
		ft_get_var_value(data->valid_env_vars[i], data->tmp_name, &data->tmp_value);
		data->exist = ft_in_env(data->tmp_name, *env);
		if (data->exist == -1)
			*env = ft_allocate_extra_pointer(*env, data->valid_env_vars[i]);
		else if (data->tmp_value)
			ft_update_value_env(data->valid_env_vars[i], env, data->exist);
		i++;
		free(data->tmp_name);
		free(data->tmp_value);
	}
	in_env(NULL, *env, 1);
}

void	ft_add_to_export(t_export *data,char **export)
{
	int	i;

	i = 0;
	while (data->valid_export_vars[i])
	{
		ft_get_var_name(data->valid_export_vars[i], &data->tmp_name);
		ft_get_var_value(data->valid_export_vars[i], data->tmp_name, &data->tmp_value);
		data->exist = ft_in_env(data->tmp_name, export);
		if (data->exist == -1)
			export = ft_allocate_extra_pointer(export, ft_create_var(data->tmp_name, data->tmp_value));
		else if (data->tmp_value)
			ft_update_value_env(data->valid_export_vars[i], &export, data->exist);
		free(data->tmp_name);
		free(data->tmp_value);
		i++;
	}
}
