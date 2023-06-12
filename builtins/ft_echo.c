/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:27 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/12 20:00:35 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[1] == 'n')
		{
			while (str[i])
			{
				if (str[i] == 'n')
					i++;
				else
					return (-1);
			}
		}
		else
			return (-1);
	}
	return (i);
}

void	ft_echo_option(t_echo *data, t_input *list, int flag)
{
	data->i = data->skip;
	while (list->arg[data->i])
	{
		data->j = 0;
		while (list->arg[data->i][data->j])
			ft_putchar_fd(list->arg[data->i][data->j++], 1);
		if (data->i < data->count - 1)
			write(1, " ", 1);
		if (data->i == data->count - 1 && flag == 1)
			write(1, "\n", 1);
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
		ft_echo_option(&data, list, 0);
	else
		ft_echo_option(&data, list, 1);
	g_vars.g_exit_status = 0;
	return ;
}
