/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:35:04 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 15:14:04 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// how many worlds before the letter indicated as the second char
int	ft_simularity_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_simularity_len_dual(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = ft_strlen(str);
	while (str && i > -1 && str[i] != c)
		i--;
	return (i);
}

void	delete_them(char **input, int start, int end)
{
	int		i;
	int		j;
	char	*re;

	re = malloc(sizeof(char) * ft_strlen((*input)) + 1);
	i = 0;
	j = 0;
	while ((*input)[i])
	{
		if (i == start && i + 1 == end)
			i += 2;
		if ((*input)[i] == '\0')
			break ;
		re[j++] = ((*input))[i++];
	}
	re[j] = '\0';
	ft_strlcpy((*input), re, i);
	free(re);
}

// that function delete start and end if they are to close...
// i use it to delete the ussless quotes
void	delete_both(char **input, int start, int end, char c)
{
	int		i;
	int		j;
	char	*re;

	re = malloc(sizeof(char) * ft_strlen((*input)) + 1);
	i = 0;
	j = 0;
	while ((*input)[i])
	{
		if (i == start && i + 1 == end && (*input)[i] == c)
			i += 2;
		re[j++] = ((*input))[i++];
	}
	re[j] = '\0';
	ft_strlcpy((*input), re, i);
	free(re);
}

// no comment
char	*take_copy(char *s1, int start, int end)
{
	int		i;
	char	*re;

	re = malloc(sizeof(char) * (end - start + 3));
	i = 0;
	while (i < end - start + 1)
	{
		re[i] = s1[start + i];
		i++;
	}
	re[i] = '\0';
	return (re);
}
