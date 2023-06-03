/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:27:11 by admansar          #+#    #+#             */
/*   Updated: 2023/06/02 20:27:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <stdio.h>

void the_start_of_the_beg_dual(char *copy, char **ls, int j, char ***holder);
void find_and_collect(char **ls, char ***holder, int *j, char *split);
void the_start_of_the_beg(char *copy, char **ls, char ***holder);
void find_and_collect_no_p(char **ls, char ***holder, int *j, char *split);

void	free_triple_array(char ***c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free_double_array(c[i]);
		i++;
	}
	free(c);
}
char	**the_repeated(char **tmp1, char **tmp2, char *str, int count)
{
	int		k;
	int		n;
	int		m;
	char	**true_re;
	char	**re;

	m = 0;
	k = -1;
	if (!tmp2)
		return (fill(tmp1));
	re = ft_calloc(sizeof(char *), ((count * ft_strlen(str)) + 1));
	while (tmp1[++k])
	{
		n = -1;
		while (tmp2[++n])
		{
			if (!ft_strcmp(tmp1[k], tmp2[n]))
			{
				re[m++] = ft_strdup(tmp1[k]);
			}
		}
	}
	true_re = fill(re);
	free_double_array(re);
	return (true_re);
}


char ***all_the_reapeated(char **holder, char *str, int h)
{
	int i;
	int m;
	char ***all;
	char **tmp1;
	char **tmp2;

	i = 0;
	m = 0;
	all = ft_calloc(sizeof(char **), h + 1);
	while (holder[i + 1])
	{
		tmp1 = ft_split(holder[i], '\6');
		tmp2 = ft_split(holder[i + 1], '\6');
		all[m++] = the_repeated(tmp1, tmp2, str, h);
		free_double_array(tmp1);
		free_double_array(tmp2);
		i++;
	}
	return (all);
}

char	**get_the_needed_array(char **holder, char **split, char *str)
{
	int		i;
	int		n;
	int		m;
	int		h;
	char	***all;
	char	**tmp1;
//	char	**tmp2;
	char	**re;

	i = 0;
	n = 0;
	m = 0;
	h = (ft_strlen(str) + ft_strcount(split));
	if (holder[i + 1])
	{
		all = all_the_reapeated(holder, str, h);
//		all = ft_calloc(sizeof(char **), h + 1);
//		while (holder[i + 1])
//		{
//			tmp1 = ft_split(holder[i], '\6');
//			tmp2 = ft_split(holder[i + 1], '\6');
//			all[m++] = the_repeated(tmp1, tmp2, str, h);
//			free_double_array(tmp1);
//			free_double_array(tmp2);
//			i++;
//		}
		i = 0;
		re = the_repeated(all[0], all[1], str, h);
		free_double_array(split);
		while (all[i])
		{
			split = fill(re);
			free_double_array(re);
			re = the_repeated(split, all[i], str, h);
			free_double_array(split);
			i++;
		}
		free_triple_array(all);
		free_double_array(holder);
		return (re);
	}
	else if (holder[i])
	{
		tmp1 = ft_split(holder[i], '\6');
		free_double_array(holder);
		free_double_array(split);
		return (tmp1);
	}
	free_double_array(split);
	return (holder);
}

char	**the_end(char *str, char **ls)
{
	char	*copy;
	int		i;
	int		j;
	char	**split;
	char	**holder;

	i = ft_strlen(str);
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
				'*') + 5));
	copy = take_copy(str, ft_simularity_len_dual(str, '*') + 1, 
			ft_strlen(str) - 1);
	the_start_of_the_beg_dual(copy, ls, j, &holder);
	if (holder[j])
		j++;
	i = 0;
	while (split[i + 1])
		find_and_collect_no_p(ls, &holder, &j, split[i++]);
	return (get_the_needed_array(holder, split, str));
}

char	**the_inner(char *str, char **ls)
{
	char	**split;
	char	**holder;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
				'*') + ft_strcount(ls) + 1));
	while (split[i])
	{
		find_and_collect_no_p(ls, &holder, &j, split[i]);
		i++;
		if (holder[j])
			j++;
	}
	return (get_the_needed_array(holder, split, str));
}

char	**the_popular_choice(char *str, char **ls)
{
	char	*copy;
	int		i;
	int		j;
	char	**split;
	char	**holder;

	i = 0;
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
				'*') + 5));
	copy = take_copy(str, 0, ft_simularity_len(str, '*') - 1);
	the_start_of_the_beg(copy, ls, &holder);
	if (holder[j])
		j++;
	copy = take_copy(str, ft_simularity_len_dual(str, '*') + 1, 
			ft_strlen(str) - 1);
	the_start_of_the_beg_dual(copy, ls, j, &holder);
	if (holder[j])
		j++;
	i = 1;
	while (split[++i])
		find_and_collect(ls, &holder, &j, split[i]);
	return (get_the_needed_array(holder, split, str));
}

void the_start_of_the_beg_dual(char *copy, char **ls, int j, char ***holder)
{
	int i;
	int h;
	int pass;
	int k;

	i = 0;
	h = ft_strlen(copy);
	pass = 1;
	k = 0;
	while (ls[k])
	{
		if (!ft_strncmp_dual(copy, ls[k], h) && pass == 1)
		{
			(*holder)[j] = ft_strdup(ls[k]);
			(*holder)[j] = ft_str_join((*holder)[j], "\6");
			pass = 0;
		}
		else if (!ft_strncmp(copy, ls[k], h))
		{
			(*holder)[j] = ft_str_join((*holder)[j], "\6");
			(*holder)[j] = ft_str_join((*holder)[j], ls[k]);
		}
		k++;
	}
	free(copy);
}



void the_start_of_the_beg(char *copy, char **ls, char ***holder)
{
	int i;
	int h;
	int pass;
	int k;

	i = 0;
	h = ft_strlen(copy);
	pass = 1;
	k = 0;
	while (ls[k])
	{
		if (!ft_strncmp(copy, ls[k], h) && pass == 1)
		{
			(*holder)[0] = ft_strdup(ls[k]);
			(*holder)[0] = ft_str_join((*holder)[0], "\6");
			pass = 0;
		}
		else if (!ft_strncmp(copy, ls[k], h))
		{
			(*holder)[0] = ft_str_join((*holder)[0], "\6");
			(*holder)[0] = ft_str_join((*holder)[0], ls[k]);
		}
		k++;
	}
	free(copy);
}

void find_and_collect_no_p(char **ls, char ***holder, int *j, char *split)
{
	int pass;
	int k;
	int h;

	pass = 1;
	k = 0;
	while (ls[k])
	{
		h = ft_strlen(ls[k]);
		if (ft_strnstr(ls[k], split, h) && pass == 1 && ls[k][0] != '.')
		{
			(*holder)[*j] = ft_strdup(ls[k]);
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			pass = 0;
		}
		else if (ft_strnstr(ls[k], split, h) && ls[k][0] != '.')
		{
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			(*holder)[*j] = ft_str_join((*holder)[*j], ls[k]);
		}
		k++;
	}
	if ((*holder)[*j])
		(*j)++;
}


void find_and_collect(char **ls, char ***holder, int *j, char *split)
{
	int pass;
	int k;
	int h;

	pass = 1;
	k = 0;
	while (ls[k])
	{
		h = ft_strlen(ls[k]);
		if (ft_strnstr(ls[k], split, h) && pass == 1)
		{
			(*holder)[*j] = ft_strdup(ls[k]);
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			pass = 0;
		}
		else if (ft_strnstr(ls[k], split, h))
		{
			(*holder)[*j] = ft_str_join((*holder)[*j], "\6");
			(*holder)[*j] = ft_str_join((*holder)[*j], ls[k]);
		}
		k++;
	}
	if ((*holder)[*j])
		(*j)++;
}

char	**the_beg(char *str, char **ls)
{
	char	*copy;
	int		i;
	int		j;
	char	**split;
	char	**holder;

	i = 0;
	j = 0;
	split = ft_split(str, '*');
	holder = ft_calloc(sizeof(char *), (ft_strcount(split) * char_counter(str,
				'*') + 5));
	while (str[i] && str[i] != '*')
		i++;
	copy = take_copy(str, 0, i - 1);
	the_start_of_the_beg(copy, ls, &holder);
	if (holder[j])
		j++;
	i = 1;
	while (split[i])
	{
		find_and_collect(ls, &holder, &j, split[i]);
		i++;
	}
	return (get_the_needed_array(holder, split, str));
}

// check if s1 is hidden in s2
int	hidden(char *s1, char *s2)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = ft_strlen(s1);
	while (s2[i])
	{
		if (s1[j] == s2[i])
		{
			j++;
			if (j == h)
				break ;
		}
		i++;
	}
	free(s1);
	if (j == h)
		return (1);
	return (0);
}

void	check_for_hidden(char *str, char ***re)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(*re))
		return ;
	tmp = ft_calloc(sizeof(char *), ft_strcount(*re) + 1);
	while ((*re)[i])
	{
		if (hidden(clean_from(str, '*'), (*re)[i]))
		{
			tmp[j] = ft_strdup((*re)[i]);
			j++;
		}
		i++;
	}
	free_double_array(*re);
	*re = fill (tmp);
	free_double_array(tmp);
}

char	**the_commun(char **str, char **ls)
{
	char	**tmp;
	char	**re;
	int		i;
	int		j;

	no_extra_(&(*str), '*');
	tmp = malloc(sizeof(char *) * (ft_strcount(ls) + 1));
	i = 0;
	j = 0;
	while (ls[i])
	{
		if (ls[i][0] != '.')
			tmp[j++] = ft_strdup(ls[i]);
		i++;
	}
	tmp[j] = NULL;
	re = fill(tmp);
	free_double_array(tmp);
	return (re);
}

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

int re_full_(char ***div, char ***re, int *j)
{
	int m;

	m = 0;
	while ((*div)[m])
	{
		(*re)[(*j)] = ft_strdup((*div)[m]);
		(*j)++;
		m++;
	}
	(*j)--;
	return (m);
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
		if (char_counter((*split)[i], '*') && !surounded_by((*split)[i],
					'\'') && !surounded_by((*split)[i], '\"'))
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
