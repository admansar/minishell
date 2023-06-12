/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:32 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/12 20:00:24 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_value_env(char *arr, char ***export, int pos)
{
	free((*export)[pos]);
	(*export)[pos] = ft_strdup(arr);
}

void	ft_fill_export_vars(t_input *list, t_export *data)
{
	data->var_nbr = ft_strcount(list->arg);
	data->valid_export_vars = ft_calloc(sizeof(char *), data->var_nbr + 1);
	data->i = 0;
	data->j = 0;
	while (list->arg[data->i])
	{
		ft_get_var(list->arg[data->i], &data->tmp_name,
			&data->tmp_value);
		if (ft_export_name_checker(data->tmp_name) == -1)
		{
			ft_printf("bash: export: `%s': not a valid identifier\n",
				list->arg[data->i]);
			g_vars.g_exit_status = 1;
		}
		else
		{
			data->valid_export_vars[data->j] = ft_strdup(list->arg[data->i]);
			ft_clean_up_name(&(data->valid_export_vars[data->j]));
			data->j++;
			g_vars.g_exit_status = 0;
		}
		free(data->tmp_name);
		free(data->tmp_value);
		data->i++;
	}
}

void	ft_check_env_var(t_export *data)
{
	data->valid_env_vars = (char **)ft_calloc(sizeof(char *), data->var_nbr
			+ 1);
	data->i = 0;
	data->j = 0;
	while (data->valid_export_vars[data->i])
	{
		if (ft_char_checker(data->valid_export_vars[data->i], '=') >= 0)
			data->valid_env_vars[data->j++]
				= ft_strdup(data->valid_export_vars[data->i++]);
		else
			data->i++;
	}
}

void	ft_export_vars(t_export *data, char **valid_vars, char ***ptr)
{
	int	i;

	i = 0;
	while (valid_vars[i])
	{
		ft_get_var_name(valid_vars[i], &data->tmp_name);
		ft_get_var_value(valid_vars[i], data->tmp_name, &data->tmp_value);
		data->exist = ft_in_env(data->tmp_name, *ptr);
		if (data->exist == -1)
			*ptr = ft_join_ptr_to_double_ptr(*ptr, valid_vars[i]);
		else if (data->tmp_value)
			ft_update_value_env(valid_vars[i], ptr, data->exist);
		free(data->tmp_name);
		free(data->tmp_value);
		i++;
	}
}

void	ft_export(char ***env, t_input *list, char ***export)
{
	t_export	data;

	ft_init_export_data(&data);
	ft_export_printer(list, *export, &data);
	ft_fill_export_vars(list, &data);
	ft_check_env_var(&data);
	ft_export_vars(&data, data.valid_export_vars, export);
	ft_export_vars(&data, data.valid_env_vars, env);
	in_env(NULL, *env, 1);
	free_double_array(data.valid_env_vars);
	free_double_array(data.valid_export_vars);
}
