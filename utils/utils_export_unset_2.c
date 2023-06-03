#include "../minishell.h"

void	ft_init_export_data(t_export *data)
{
	data->valid_export_vars = NULL;
	data->valid_env_vars = NULL;
	data->env_vars = NULL;
	data->tmp_name = NULL;
	data->tmp_value = NULL;
	data->tmp1 = NULL;
	data->tmp2 = NULL;
	data->arr = NULL;
	data->var_nbr = 0;
	data->j = 0;
	data->i = 0;
	data->count = 0;
	data->ret = 0;
	data->exist = 0;
	data->len = 0;
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
