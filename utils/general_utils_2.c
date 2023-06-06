/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:05 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 18:21:24 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_join_double_ptr_to_ptr(char *str, char **arr1)
{
	int		len;
	int		i;
	char	**joined;

	len = ft_strcount(arr1);
	joined = (char **)ft_calloc(sizeof(char *), len + 2);
	i = -1;
	joined[0] = ft_strdup(str);
	while (arr1[++i])
		joined[i + 1] = ft_strdup(arr1[i]);
	free_double_array(arr1);
	return (joined);
}

char	**ft_join_ptr_to_double_ptr(char **arr1, char *str)
{
	int		len;
	int		i;
	char	**joined;

	len = ft_strcount(arr1);
	joined = (char **)ft_calloc(sizeof(char *), len + 3);
	i = -1;
	while (arr1[++i])
		joined[i] = ft_strdup(arr1[i]);
	joined[i] = ft_strdup(str);
	free_double_array(arr1);
	return (joined);
}

// join 2 double pointer
char	**ft_double_array_joiner(char **arr1, char **arr2)
{
	int		len;
	int		i;
	int		j;
	char	**joined;

	len = ft_strcount(arr1) + ft_strcount(arr2) + 1;
	joined = (char **)ft_calloc(sizeof(char *), len + 1);
	i = -1;
	if (arr1)
		while (arr1[++i])
			joined[i] = arr1[i];
	j = -1;
	if (arr2)
		while (arr2[++j])
			joined[i + j] = arr2[j];
	return (joined);
}

void	ft_join_str_to_double_array(char ***arg, char **to_join)
{
	int		len;
	int		i;
	char	**joined;

	len = ft_strcount((*arg));
	joined = (char **)ft_calloc(sizeof(char *), len + 2);
	i = -1;
	while ((*arg)[++i])
		joined[i] = ft_strdup((*arg)[i]);
	joined[i] = ft_strdup(*to_join);
	free_double_array((*arg));
	(*arg) = joined;
}

// check if my var is in the envirement
int	ft_in_env(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)) && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
