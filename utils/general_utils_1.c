/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:02 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 18:21:56 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (-1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((*str1 || *str2))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

// check if the char c is found inside of the string str
int	inside_of(char *str, char c)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str) - 1;
	if (len > 0)
		if (str[len] == c)
			len--;
	while (i < len && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// check if my char c is in my str and return the its index if exist | -1 if not
int	ft_char_checker(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// extract the variable name from the var and assign to the given var_name
void	ft_get_var_name(char *var, char **var_name)
{
	int	ret;
	int	len;

	ret = ft_char_checker(var, '=');
	if (ret == -1)
	{
		len = ft_strlen(var);
		*var_name = take_copy(var, 0, len);
	}
	else
		*var_name = take_copy(var, 0, ret - 1);
}

// extract the variable name from the var and assign to the given var_name
void	ft_get_var_value(char *var, char *var_name, char **var_value)
{
	int	i;
	int	ret;
	int	len;

	ret = ft_char_checker(var, '=');
	if (ret == -1)
		*var_value = NULL;
	else
	{
		ret++;
		len = ft_strlen(var) - ft_strlen(var_name);
		*var_value = (char *)ft_calloc(sizeof(char), len + 3);
		i = -1;
		while (++i < len)
			(*var_value)[i] = var[i + ret];
	}
}
