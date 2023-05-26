#include "minishell.h"

// check if the option given is valid
int	ft_check_valid_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (-1);
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] == 'n')
				i++;
			else
				return (-1);
		}
	}
	return (i);
}

void	ft_echo_no_option(t_echo *data, t_input *list)
{
	data->i = data->skip;
	while (list->arg[data->i])
	{
		data->j = 0;
		while (list->arg[data->i][data->j])
		{
			if (list->arg[data->i][data->j] == '$'
				&& list->arg[data->i][data->j + 1] == '?')
			{
				printf("%d", g_vars.g_exit_status);
				data->j++;
			}
			else
				printf("%c", list->arg[data->i][data->j]);
			data->j++;
		}
		if (data->i < data->count - 1)
			printf(" ");
		if (data->i == data->count - 1)
			printf("\n");
		data->i++;
	}
}

void	ft_echo_with_option(t_echo *data, t_input *list)
{
	data->i = data->skip;
	while (list->arg[data->i])
	{
		data->j = 0;
		while (list->arg[data->i][data->j])
		{
			if (list->arg[data->i][data->j] == '$'
			&& list->arg[data->i][data->j + 1] == '?')
			{
				printf("%d", g_vars.g_exit_status);
				data->j++;
			}
			else
				printf("%c", list->arg[data->i][data->j]);
			data->j++;
		}
		if (data->i < data->count - 1)
			printf(" ");
		data->i++;
	}
}

void	ft_echo(t_input *list)
{
	t_echo	data;

	data.count = ft_strcount(list->arg);
	if (!data.count)
		printf("\n");
	data.i = 0;
	data.option = 0;
	data.skip = 0;
	while (list->arg[data.skip])
	{
		if (ft_check_valid_option(list->arg[data.skip]) != -1)
			data.skip++;
		else
			break ;
	}
	if (data.skip > 0)
		data.option = 1;
	if (data.option)
		ft_echo_with_option(&data, list);
	else
		ft_echo_no_option(&data, list);
	g_vars.g_exit_status = 0;
	return ;
}
