/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:37 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 18:34:21 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_remove(char **ptr, int pos)
{
	char	**new_ptr;
	int		len;
	int		i;
	int		j;

	if (pos < 0)
		return (ptr);
	len = ft_strcount(ptr);
	new_ptr = (char **)ft_calloc(sizeof(char *), len + 1);
	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (i == pos)
			i++;
		else
		{
			new_ptr[j] = ft_strdup(ptr[i]);
			i++;
			j++;
		}
	}
	free_double_array(ptr);
	return (new_ptr);
}

void	ft_fill_unset_vars(t_input *list, t_export *data)
{
	data->var_nbr = ft_strcount(list->arg);
	data->valid_export_vars = ft_calloc(sizeof(char *), data->var_nbr + 1);
	data->i = 0;
	data->j = 0;
	while (list->arg[data->i])
	{
		ft_get_var(list->arg[data->i], &data->tmp_name,
			&data->tmp_value);
		if (ft_unset_name_checker(data->tmp_name) == -1)
		{	
			ft_printf("bash: unset: `%s': not a valid identifier\n",
				list->arg[data->i]);
			g_vars.g_exit_status = 2;
		}
		else
		{
			data->valid_export_vars[data->j] = ft_strdup(list->arg[data->i]);
			ft_clean_up_name(&(data->valid_export_vars[data->j++]));
		}
		free(data->tmp_name);
		free(data->tmp_value);
		data->i++;
	}
}

void	ft_unset_vars(t_export *data, char ***ptr)
{
	int	i;

	i = 0;
	while (data->valid_export_vars[i])
	{
		data->exist = ft_in_env(data->valid_export_vars[i], *ptr);
		if (data->exist >= 0)
			*ptr = ft_remove(*ptr, data->exist);
		i++;
	}
}

void	ft_unset(char ***env, t_input *list, char ***export)
{
	t_export	data;

	ft_init_export_data(&data);
	ft_fill_unset_vars(list, &data);
	ft_unset_vars(&data, export);
	ft_unset_vars(&data, env);
	in_env(NULL, *env, 1);
	free_double_array(data.valid_export_vars);
	g_vars.g_exit_status = 0;
}
