/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:02:26 by admansar          #+#    #+#             */
/*   Updated: 2023/06/12 20:00:18 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	disable(char **str, char c)
{
	int		i;
	int		j;
	char	*re;

	re = ft_calloc(sizeof(char), (ft_strlen(*str)));
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != c)
		{
			re[j++] = (*str)[i++];
		}
		else
			i++;
	}
	free(*str);
	*str = ft_strdup(re);
	free(re);
}

void	no_extra_(char **ptr, char c)
{
	int		i;
	int		j;
	int		k;
	char	*re;

	if (!consecutive(*ptr, c))
		return ;
	re = ft_calloc(sizeof(char), ft_strlen(*ptr) + 1);
	i = 0;
	j = 0;
	while ((*ptr)[i])
	{
		k = 0;
		while ((*ptr)[i] == c && (*ptr)[i])
		{
			k = 1;
			i++;
		}
		if (i > 0 && k == 1)
			i--;
		re[j++] = (*ptr)[i++];
	}
	free(*ptr);
	*ptr = ft_strdup(re);
	free(re);
}

// print the double array for me
void	printer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] == '?' && ptr[i][1] == '=')
			i++;
		else
			printf("%s\n", ptr[i++]);
	}
	g_vars.g_exit_status = 0;
}

char	**fill(char **str)
{
	int		i;
	char	**re;

	re = ft_calloc(sizeof(char *), ft_strcount(str) + 1);
	i = 0;
	while (str[i])
	{
		re[i] = ft_strdup(str[i]);
		i++;
	}
	return (re);
}

void	free_double_array(char **c)
{
	int	i;

	i = 0;
	if (c)
	{
		while (c[i])
		{
			free(c[i]);
			c[i++] = NULL;
		}
	}
	free(c);
	c = NULL;
}
