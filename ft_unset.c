#include "minishell.h"

void ft_unset(char ***env, char *name)
{
	int index;
	int i;

	index = ft_in_env(name , *env);
	i = 0;
	while ((*env)[index][i])
	{
		(*env)[index][i] = '\2';
		i++;
	}
}
