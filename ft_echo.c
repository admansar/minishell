
#include "minishell.h"

int ft_check_valid(char *str)
{
	int i;

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

void ft_echo(t_input *list)
{
	(void)list;
	int i;
	int count;
	int option;
	int skip;
	int j;

	count = ft_strcount(list->arg);
	if (!count)
		printf("\n");
	i = 0;
	option = 0;
	skip = 0;
	while (list->arg[skip])
	{
		if (ft_check_valid(list->arg[skip]) != -1)
			skip++;
		else
			break;
	}
	if (skip > 0)
		option = 1;
	if (option)
	{
		i = skip;
		while (list->arg[i])
		{
			j = 0;
			while (list->arg[i][j])	
			{
				if (list->arg[i][j] == '$' && list->arg[i][j+1] == '?')
				{
					printf ("%d", g_vars.g_exit_status);
					j++;
				}
				else
					printf("%c", list->arg[i][j]);
				j++;
			}
			if (i < count - 1)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = skip;
		while (list->arg[i])
		{
			j = 0;
			while (list->arg[i][j])	
			{
				if (list->arg[i][j] == '$' && list->arg[i][j+1] == '?')
				{
					printf ("%d", g_vars.g_exit_status);
					j++;
				}
				else
					printf("%c", list->arg[i][j]);
				j++;
			}
			if (i < count - 1)
				printf(" ");
			if (i == count - 1)
				printf("\n");
			i++;
		}
	}
	g_vars.g_exit_status = 0;
	return;
}
