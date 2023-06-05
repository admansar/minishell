/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:27:11 by admansar          #+#    #+#             */
/*   Updated: 2023/06/04 14:55:44 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_sure(char **str, char **ls)
{
	char	**re;

	if (char_counter((*str), '*') == (int)ft_strlen(*str))
		re = the_commun(str, ls);
	else if (surounded_by(*str, '*'))
		re = the_inner(*str, ls);
	else if ((*str)[0] != '*' && (*str)[ft_strlen(*str) - 1] == '*')
		re = the_beg(*str, ls);
	else if ((*str)[0] == '*' && (*str)[ft_strlen(*str) - 1] != '*')
		re = the_end(*str, ls);
	else
		re = the_popular_choice(*str, ls);
	check_for_hidden(*str, &re);
	return (re);
}

void	remake(char ***split, int *i, char **div)
{
	char	**re;
	int		n;
	int		m;
	int		j;

	if (!div)
		return ;
	re = ft_calloc(sizeof(char *), (ft_strcount(*split) + ft_strcount(div)
				+ 1));
	n = 0;
	j = 0;
	while ((*split)[n])
	{
		if (n == (*i))
			m = re_full_(&div, &re, &j);
		else
			re[j] = ft_strdup((*split)[n]);
		j++;
		n++;
	}
	(*i) += m - 1;
	free_double_array(*split);
	*split = fill(re);
	free_double_array(re);
}

int	count_for_ls(DIR *dir)
{
	int				i;
	struct dirent	*entry;

	entry = readdir(dir);
	i = 1;
	while (entry)
	{
		entry = readdir(dir);
		i++;
	}
	return (i);
}

char	**list_current_directory_content(void)
{
	int				i;
	DIR				*dir;
	char			**ls;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	ls = ft_calloc(sizeof(char *), (count_for_ls(dir) + 1));
	closedir(dir);
	dir = opendir(".");
	entry = readdir(dir);
	i = 0;
	while (entry)
	{
		ls[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (ls);
}

void	wildcard(char ***split)
{
	int		i;
	int		count;
	char	**ls;
	char	**re;

	ls = list_current_directory_content();
	if (!ls)
		return ;
	i = 0;
	count = mega_counter((*split), '*');
	while ((*split)[i])
	{
		if (char_counter((*split)[i], '*') && !surounded_by((*split)[i], '\'')
				&& !surounded_by((*split)[i], '\"'))
		{
			re = make_sure(&(*split)[i], ls);
			if (re && re[0])
				remake(split, &i, re);
			free_double_array(re);
		}
		if (++i >= ft_strcount(*split))
			break ;
	}
	free_double_array(ls);
}
