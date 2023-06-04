/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:53:53 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 13:53:56 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// count how many characters in the first world
int	char_counter(const char *co, char c)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (co && co[++i])
		if (co[i] == c)
			counter++;
	return (counter);
}

// print error
void	error_print(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	free(s2);
	ft_putchar_fd('\n', 2);
}

// if a string is surounded by the charactere specified it returns 1
int	surounded_by(char *str, char c)
{
	int	h;

	h = ft_strlen(str);
	if (h > 0)
	{
		while (h > 0 && str[h - 1] == ' ')
			h--;
		if (str[0] == c && str[h - 1] == c)
			return (1);
	}
	return (0);
}

// copy without beeing surounded by double quote
char	*clean_copy(char *c)
{
	int		i;
	int		j;
	int		k;
	char	*re;

	if (surounded_by(c, '\"'))
	{
		re = ft_calloc(sizeof(char), ft_strlen(c) + 1);
		i = 0;
		k = 0;
		j = 0;
		while (c[i] && k < 2)
		{
			if (c[i] != '\"')
			{
				re[j] = c[i];
				j++;
			}
			else
				k++;
			i++;
		}
		return (re);
	}
	return (ft_strdup(c));
}

// just to get the len of the longest world
// int max_len(char **str)
//{
//	int i;
//	int max;
//	int	h;
//
//	max = ft_strlen(str[0]);
//	i = 0;
//	while (str[i])
//	{
//		h = ft_strlen(str[i]);
//		if (h > max)
//			max = h;
//		i++;
//	}
//	return (max);
//}

void	delete_both_double(t_parse *pars, char **input)
{
	if (pars->start == pars->end - 1)
	{
		if (pars->start > 0)
			if ((*input)[pars->start - 1] == ' ')
				pars->used = 0.5;
		if (pars->end < pars->len)
			if ((*input)[pars->end + 1] == ' ' || pars->end + 1 == pars->len)
				pars->used += 0.5;
		if (pars->used != 1)
		{
			delete_both(input, pars->start, pars->end, '\"');
			pars->i = -1;
			pars->start = 0;
			pars->end = 0;
			pars->taken = 1;
		}
	}
}
