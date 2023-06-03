#include "../minishell.h"

void	ft_exit(t_input *list)
{
	if (list->arg[0])
	{
		if (have_just_digits(list->arg[0]) && !list->arg[1])
		{
			exit(ft_atoi(list->arg[0]));
		}
		else if (!have_just_digits(list->arg[0]))
		{
			ft_printf("bash: exit: %s: numeric argument required\n",
					list->arg[0]);
			exit(255);
		}
		else if (list->arg[0] && list->arg[1])
		{
			ft_printf("bash: exit: too many arguments\n");
			g_vars.g_exit_status = 1;
			return ;
		}
	}
	else
	{
		exit(g_vars.g_exit_status);
	}
}
