/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_join_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:06:58 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:07:01 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the dual of qoutes and double qoutes
char	dual(char c)
{
	if (c == '\'')
		return ('\"');
	return ('\'');
}

void	delete_the_chosen(t_expand *var, char **ptr, int number_of_char, char c)
{
	while ((*ptr)[var->i])
	{
		if (var->k == number_of_char && (*ptr)[var->i] == dual(c))
		{
			var->tmp[var->j++] = c;
			var->k = number_of_char + 1;
		}
		if (var->k == number_of_char && (*ptr)[var->i] == ' ')
		{
			var->tmp[var->j++] = c;
			var->tmp[var->j++] = ' ';
			var->i++;
			if ((unsigned int)var->i == ft_strlen((*ptr)))
				break ;
		}
		if ((*ptr)[var->i] != c)
			var->tmp[var->j++] = (*ptr)[var->i];
		else
			var->k++;
		var->i++;
	}
}

// delete the usless iner things
void	delete_them_inside(char **ptr, char c)
{
	t_expand	*var;
	int			number_of_char;

	var = malloc(sizeof(t_expand));
	var->i = 0;
	var->j = 0;
	var->k = 0;
	number_of_char = char_counter(*ptr, c);
	var->tmp = ft_calloc(sizeof(char), (ft_strlen(*ptr) + 3));
	var->tmp[var->j++] = c;
	delete_the_chosen(var, ptr, number_of_char, c);
	if (char_counter(var->tmp, c) != 2)
		var->tmp[var->j++] = c;
	var->tmp[var->j] = '\0';
	free(*ptr);
	*ptr = malloc(sizeof(char) * (ft_strlen(var->tmp) + 1));
	ft_strlcpy(*ptr, var->tmp, ft_strlen(var->tmp) + 1);
	free(var->tmp);
	free(var);
}

void	check_delete(char **str)
{
	int	h;

	h = ft_strlen(*str);
	if (h > 0)
	{
		while (h > 0 && (*str)[h - 1] == ' ')
		{
			(*str)[h - 1] = '\0';
			h--;
		}
	}
}

void	no_surounded_anymore(char **str)
{
	if (surounded_by((*str), '\''))
		disable(&(*str), '\'');
	else if (surounded_by((*str), '\"'))
		disable(&(*str), '\"');
}
