/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:09:12 by admansar          #+#    #+#             */
/*   Updated: 2023/06/03 23:09:15 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//how many worlds before the letter indicated as the second char 
int ft_simularity_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int ft_simularity_len_dual(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = ft_strlen (str);
	while (str && i > -1 && str[i] != c)
		i--;
	return (i);
}

void delete_them(char **input, int start, int end)
{
	int i;
	int j;
	char *re;

	re = malloc (sizeof (char) * ft_strlen((*input)) + 1);
	i = 0;
	j = 0;
	while ((*input)[i])
	{
		if (i == start && i + 1 == end)
			i += 2;
		if ((*input)[i] == '\0')
			break;
		re[j++] = ((*input))[i++];
	}
	re[j] = '\0';
	ft_strlcpy((*input), re, i);
	free (re);
}

//that function delete start and end if they are to close... i use it to delete the ussless quotes
void delete_both(char **input, int start, int end, char c)
{
	int i;
	int j;
	char *re;

	re = malloc (sizeof (char) * ft_strlen((*input)) + 1);
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
	free (re);
}

//no comment
char *take_copy(char *s1, int start, int end)
{
	int i;
	char *re;

	re = malloc (sizeof(char) * (end - start + 3));
	i = 0;
	while (i < end - start + 1/* && s1[start + i]*/)
	{
		re[i] = s1[start + i];
		i++;
	}
	re[i] = '\0';
	return (re);
}

//count how many characters in the first world
int char_counter(const char *co, char c)
{
	int i;
	int counter;

	i = -1;
	counter = 0;
	while (co && co[++i])
		if (co[i] == c)
			counter++;
	return (counter);
}

// print error 
void error_print(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	free (s2);
	ft_putchar_fd('\n', 2);
}

// if a string is surounded by the charactere specified it returns 1 
int surounded_by(char *str, char c)
{
	int h;

	h = ft_strlen (str);
	if (h > 0)
	{
		while (h > 0 &&  str[h - 1] == ' ')
			h--;
		if (str[0] == c && str[h - 1] == c)
			return (1);
	}
	return (0);
}

//copy without beeing surounded by double quote
char *clean_copy(char *c)
{
	int i;
	int j;
	int k;
	char *re;

	if (surounded_by(c, '\"'))
	{
		re = ft_calloc (sizeof (char), ft_strlen(c) + 1);
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

//just to get the len of the longest world
int max_len(char **str)
{
	int i;
	int max;
	int	h;

	max = ft_strlen(str[0]);
	i = 0;
	while (str[i])
	{
		h = ft_strlen(str[i]);
		if (h > max)
			max = h;
		i++;
	}
	return (max);
}

void delete_both_double (t_parse *pars, char **input)
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

void d_delete(char **input) // d for double quotes
{
	t_parse pars;

	pars.i = 0;
	pars.taken = 1;
	pars.start = 0;
	pars.end = 0;
	pars.len = ft_strlen (*input) + 1;
	while ((*input)[pars.i])
	{
		pars.used = 0;
		if ((*input)[pars.i] == '\"' && pars.taken == 1)
		{
			pars.start = pars.i;
			pars.taken = 0;
		}
		else if ((*input)[pars.i] == '\"' && pars.taken == 0)
		{
			pars.end = pars.i;
			pars.taken = 1;
		}
		delete_both_double (&pars, input);
		pars.i++;
	}
}

void delete_both_single(t_parse *pars, char **input)
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
			delete_both(input, pars->start, pars->end, '\'');
			pars->i = -1;
			pars->start = 0;
			pars->end = 0;
			pars->taken = 1;
		}
	}
}

void s_delete(char **input) // s for single quotes
{	
	t_parse pars;

	pars.i = 0;
	pars.taken = 1;
	pars.start = 0;
	pars.end = 0;
	pars.len = ft_strlen (*input) + 1;
	while ((*input)[pars.i])
	{
		if ((*input)[pars.i] == '\'' && pars.taken == 1)
		{
			pars.start = pars.i;
			pars.taken = 0;
		}
		else if ((*input)[pars.i] == '\'' && pars.taken == 0)
		{
			pars.end = pars.i;
			pars.taken = 1;
		}
		delete_both_single(&pars, input);
		pars.i++;
	}
}

void look_for_partner(t_parse *pars, char ***new_str, char **input)
{
	(*new_str)[pars->j] = ft_calloc (sizeof (char), (ft_strlen((*input)) + 1));
	pars->k = 0;
	while ((*input)[pars->i] && (*input)[pars->i] != '\''
			&& (*input)[pars->i] != '\"')
	{ 
		(*new_str)[pars->j][pars->k] = (*input)[pars->i];
		pars->k++;
		pars->i++;
	}
	(*new_str)[pars->j][pars->k] = '\0';
	should_i_replace_them(&(*new_str)[pars->j]);
	make_some_space(&(*new_str)[pars->j]);
	pars->j++;
	pars->i--;
}

//no need to the comment !!
//anyway this function delete the double qoutes that start and end with nothing inside
void delete_non_sense(char **input)
{
	(*input) = ft_str_join((*input), " ");
	d_delete(input);
	s_delete(input);
}

void split_without_weast_utils(t_parse *pars, char ***new_str, char **input)
{
	if (((*input)[pars->i] == '\"'||(*input)[pars->i] == '\'')
				&& pars->taken == 1)
		{
			pars->start = pars->i;
			pars->taken = 0;
		}
		else if (pars->taken == 1) 
			look_for_partner(pars, new_str, input);
		else if (((*input)[pars->i] == '\"'||(*input)[pars->i] == '\'')	&& pars->taken == 0 && (*input)[pars->start] == ((*input)[pars->i]))
		{
			pars->end = pars->i;
			if ((*input)[pars->i + 1] == ' ')
				pars->end = ++pars->i;
			pars->taken = 1;
		}
		if (pars->start < pars->end)
		{
			(*new_str)[pars->j++] = take_copy((*input), pars->start, pars->end);
			if (!surounded_by((*new_str)[pars->j - 1], '\"'))
				should_i_replace_them(&(*new_str)[pars->j - 1]);
			pars->start = pars->end;
		}
		pars->i++;
}

//better for cheking errors the advantage of it that i split the double quote without waisting the double quotes
char **split_without_weast(char **input) 
{
	t_parse pars;
	char **new_str;

	new_str = malloc (sizeof (char *) * ft_strlen((*input)));
	pars.start = 0;
	pars.end = 0;
	pars.taken = 1;
	pars.j = 0;
	pars.i = 0;
	while ((*input)[pars.i])
		split_without_weast_utils(&pars, &new_str, input);
	new_str[pars.j] = NULL;
	if (pars.start > pars.end)
	{
		free_double_array(new_str);
		new_str = NULL;
		return (NULL);
	}
	return (new_str);
}

void search_and_replace(t_parse *pars, char **input)
{
		if ((*input)[pars->i] == '\'' && pars->taken == 1)
		{
			pars->start = pars->i;
			pars->taken = 0;
		}
		else if ((*input)[pars->i] == '\'' && pars->taken == 0)
		{
			pars->end = pars->i;
			pars->taken = 1;
		}
		if (pars->start < pars->end)
		{
			pars->str = take_copy((*input), pars->start, pars->end);
			if (!char_counter(pars->str, '\"') && !char_counter(pars->str, '$'))
			{
				(*input)[pars->start] = '\"';
				(*input)[pars->end] = '\"';
			}
			free (pars->str);
			pars->str = NULL;
			pars->start = pars->end;
		}
		pars->i++;
}

// in some cases the single quote act exactly like double quotes ... then should i replace them in that case ?
void should_i_replace_them(char **input)
{
	t_parse pars;

	pars.start = 0;
	pars.end = 0;
	pars.taken = 1;
	pars.i = 0;
	while ((*input)[pars.i])
		search_and_replace(&pars, input);
}

void i_should_replace_single(t_parse *pars, char **input)
{
	if ((*input)[pars->i] == '\'' && pars->taken == 1)
	{
		pars->start = pars->i;
		pars->taken = 0;
	}
	else if ((*input)[pars->i] == '\'' && pars->taken == 0)
	{
		pars->end = pars->i;
		pars->taken = 1;
	}
	if (pars->start < pars->end)
	{
		pars->str = take_copy((*input), pars->start, pars->end);
		if (!char_counter(pars->str, '\"'))
		{
			(*input)[pars->start] = '\"';
			(*input)[pars->end] = '\"';
		}
		free (pars->str);
		pars->str = NULL;
		pars->start = pars->end;
	}
	pars->i++;
}


// i mean the name is really clear
void i_should_replace_them(char **input)
{
	t_parse pars;

	pars.start = 0;
	pars.end = 0;
	pars.taken = 1;
	pars.i = 0;
	while ((*input)[pars.i])
		i_should_replace_single(&pars, input);
}

void free_double_array(char **c)
{
	int	i;

	i = 0;
	if (c)
		while (c[i])
		{
			free(c[i]);
			c[i++] = NULL;
		}
	free(c);
	c = NULL;
}

void make_space_split_join(char **new_str, char ***split, int i)
{
	make_some_space(&(new_str)[i]);
	(*split) = my_spliter(new_str[i], 0, 0, 0);
	if (new_str[i][ft_strlen(new_str[i]) - 1] == ' ')
		(*split)[ft_strcount(*split) - 1]
		   	= ft_str_join((*split)[ft_strcount(*split) - 1], " ");
}


//the best split for the project 
char **ultra_split(char **new_str , char **input)
{
	char **split;
	char **str_pro_max;
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	k = 0;
	str_pro_max = ft_calloc(sizeof(char *), ft_strlen((*input)));
	while (new_str[++i])
		if (!surounded_by(new_str[i], '\"')	&& char_counter(new_str[i], ' ')
			  	&& !surounded_by(new_str[i], '\''))
		{
			make_space_split_join(new_str, &split, i);
			j = 0;
			while (split[j])
				str_pro_max [k++] = ft_strdup(split[j++]);
			free_double_array(split);
		}
		else
			str_pro_max[k++] = ft_strdup(new_str[i]);		
	return (str_pro_max);
}

void delete_array_form_double_array(int *i, char ***str_pro_max)
{
	int j;

	j = (*i) + 1;
	while ((*str_pro_max)[j + 1])
	{
		free ((*str_pro_max)[j]);
		(*str_pro_max)[j] = ft_strdup((*str_pro_max)[j + 1]);
		j++;
	}
	free((*str_pro_max)[j]);
	(*str_pro_max)[j] = NULL;
	(*i) = -1;
}

//join the string to the next one that should be joined with 
void the_joiner(char ***str_pro_max)
{
	int i;
	int j;
	int k;
	int h;

	i = 0;
	k = 0;
	j = 0;
	if (i + 1 < ft_strcount(*str_pro_max))
		while ((*str_pro_max)[i + 1])
		{
			h = ft_strlen((*str_pro_max)[i]) - 1;
			k = 0;
			if ((*str_pro_max)[i][h] != ' ' && !k && (*str_pro_max)[i + 1][0] != '>' && (*str_pro_max)[i + 1][0] != '<' && (*str_pro_max)[i + 1][0] != '|')
			{
				if (char_counter((*str_pro_max)[i + 1], '$') && surounded_by((*str_pro_max)[i + 1], '\''))
					exchange (&(*str_pro_max)[i + 1], '\'', '\"');
				(*str_pro_max)[i] = ft_str_join((*str_pro_max)[i], (*str_pro_max)[i + 1]);
				delete_array_form_double_array(&i, str_pro_max);
			}
			i++;
		}
}

//print the double array for me 
void printer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] == '?' && ptr[i][1] == '=')
			i++;
		else
			printf ("%s\n", ptr[i++]);
	}
	g_vars.g_exit_status = 0;
}

//the dual of qoutes and double qoutes 
char dual(char c)
{
	if (c == '\'')
		return ('\"');
	return ('\'');
}

void delete_the_chosen(t_expand *var, char **ptr, int number_of_char, char c)
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
				break;
		}
		if ((*ptr)[var->i] != c)
			var->tmp[var->j++] = (*ptr)[var->i];
		else  
			var->k++;
		var->i++;
	}
}


//delete the usless iner things
void delete_them_inside(char **ptr, char c)
{
	t_expand var;
	int		number_of_char;

	var.i = 0;
	var.j = 0;
	var.k = 0;
	number_of_char = char_counter(*ptr, c);
	var.tmp = ft_calloc (sizeof(char), (ft_strlen(*ptr) + 3));
	var.tmp[var.j++] = c;
	delete_the_chosen(&var, ptr, number_of_char, c);
	if (char_counter(var.tmp, c) != 2)
		var.tmp[var.j++] = c;
	var.tmp[var.j] = '\0';
	free (*ptr);
	*ptr = malloc (sizeof (char) * (ft_strlen(var.tmp) + 1));
	ft_strlcpy(*ptr, var.tmp, ft_strlen(var.tmp) + 1);
	free(var.tmp);
}

void check_delete(char **str)
{	
	int h;

	h = ft_strlen (*str);
	if (h > 0)
	{
		while (h > 0 && (*str)[h - 1] == ' ')
		{
			(*str)[h - 1] = '\0';
			h--;
		}
	}
}

void disable(char **str, char c)
{
	int i;
	int j;
	char *re;


	re = ft_calloc (sizeof (char), (ft_strlen (*str)));
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
	free (*str);
	*str = ft_strdup(re);
	free (re);
}

void no_surounded_anymore(char **str)
{
	if (surounded_by((*str), '\''))
		disable (&(*str), '\'');
	else if (surounded_by((*str), '\"'))
		disable (&(*str), '\"');
}

void delete_last_spaces(char ***str)
{
	int i;

	i = 0;
	while ((*str)[i])
		check_delete(&(*str)[i++]);
}

//no comment
void no_etxra_qoutes(char ***str)
{
	int	i;
	int d;
	int s;

	i = 0;
	while ((*str)[i])
	{
		s = ft_simularity_len ((*str)[i], '\'');
		d = ft_simularity_len ((*str)[i], '\"');
		if (s < d && char_counter((*str)[i], '\'') >= 2)
			delete_them_inside (&(*str)[i], '\'');
		else if (d < s  && char_counter((*str)[i], '\"') >= 2)
			delete_them_inside (&(*str)[i], '\"');
		i++;
	}
	delete_last_spaces(str);
}

void space_append_heardoc(char **tmp, int *i, int *j, int type)
{
	if (type == 2)
	{
		(*tmp)[(*j)++] = ' ';
		(*tmp)[(*j)++] = '>';
		(*tmp)[(*j)++] = '>';
		(*tmp)[(*j)++] = ' ';
		(*i)+=2;
	}
	else if (type == 4)
	{
		(*tmp)[(*j)++] = ' ';
		(*tmp)[(*j)++] = '<';
		(*tmp)[(*j)++] = '<';
		(*tmp)[(*j)++] = ' ';
		(*i)+=2;
	}
}

void space_char(char **tmp, int *i, int *j, char c)
{
	(*tmp)[(*j)++] = ' ';
	(*tmp)[(*j)++] = c;
	(*tmp)[(*j)++] = ' ';
	(*i)++;
}

int size_to_allocate(char **str)
{
	return (ft_strlen((*str)) + (char_counter((*str),'>') * 2)
		   	+ (char_counter((*str),'<') * 2)
			+ (char_counter((*str),'|') * 2) + 1);
}

// making space to let the "rederections" easy to detect inside by the ultra_split 
void make_some_space(char **str) 
{
	char *tmp;
	int j;
	int i;

	j = 0;  
	i = 0;
	if (!((char_counter((*str),'>')) || (char_counter((*str),'<'))
		   	||	(char_counter((*str),'|'))))
		return ;
		tmp = ft_calloc(sizeof(char), size_to_allocate(str));
		while ((*str)[i])
			if ((*str)[i] == '>' && (*str)[i + 1] == '>')
				space_append_heardoc(&tmp, &i, &j, 2);
			else if ((*str)[i] == '>')
				space_char(&tmp, &i, &j, '>');
			else if ((*str)[i] == '|')
				space_char(&tmp, &i, &j, '|');
			else if ((*str)[i] == '<' && (*str)[i + 1] == '<')
				space_append_heardoc(&tmp, &i, &j, 4);
			else if ((*str)[i] == '<')
				space_char(&tmp, &i, &j, '<');
			else 
				tmp[j++] = (*str)[i++];
		free((*str));
		(*str) = tmp;
}


// wanna make a copy of your double array , use fill function ... its your friend
char **fill(char **str)
{
	int i;
	char **re;

	re = ft_calloc(sizeof(char *), ft_strcount(str) + 1);
	i = 0;
	while (str[i])
	{
		re[i] = ft_strdup(str[i]);
		i++;
	}
	return (re);
}

int in_env(char *ptr, char **env, int flag) 
{
	static char **the_env;
	int k;

	k = -1;
	if (flag == 1)
	{
		if (!the_env)
			the_env = fill(env);
		else if (env)
		{
			free_double_array(the_env);
			the_env = fill(env);
		}
		return (-2);
	}
	while (the_env[++k])
		if (!ft_strncmp(the_env[k], ptr, ft_strlen (ptr))
			   	&& the_env[k][ft_strlen (ptr)] == '=')
			return (k);
	return (-1);
}

int checking_direction_expand(char *str, char **env)
{
	int end;
	char *tmp;

	end = ft_simularity_len(str, '$');
	while (str[end + 1] && (ft_isalpha(str[end + 1])
			   	|| ft_isdigit((str[end + 1]))
			   	|| (str[end + 1] == '_')))
		end++;
	tmp = take_copy(str, ft_simularity_len(str, '$') + 1, end);
	end = in_env(tmp, NULL, 0);
	if (end >= 0)
	{
		if (!char_counter(env[end], ' '))
		{
			free (tmp);
			return (1);
		}
	}
	else
	{
		free (tmp);
		return (0);
	}
	free (tmp);
	return (1);
}

int recursive_why_not(char *str, char **env)
{
	int i;
	char **split;
	int end;

	split = ft_split(str, ' ');
	i = -1;
	end = 1;
	while (split[++i])
		if (char_counter(split[i], '$'))
		{
			if (i > 0)
				end = checking_direction(split[i], split[i - 1], env);
			else
				end = checking_direction(split[i], NULL, env);

			break;	
		}
	free_double_array(split);
	return (end);
}

int recursive_untill_found(char *str, char **env)
{
	char **split;
	int i;
	int end;

	end = 1;
	split = ft_split(str, ' ');
	i = -1;		
	while (split[++i])
		if (char_counter(split[i], '$'))
			if (i > 0)
			{
				end = checking_direction(split[i], split[i - 1], env);
				break;
			}	
	free_double_array(split);
	return (end);
}

int	checking_direction(char *str, char *behind_str, char **env) //this function take a look the expand to make it more exact ...
{
	if (behind_str)
	{
		if (!surounded_by(str, '\'') && (!ft_strncmp(behind_str
						+ ft_simularity_len(behind_str, '<'), "<<", 2)))
			return (2);
		else if (!surounded_by(str, '\'') &&
				!surounded_by(str, '\"') && !char_counter(str, ' ')
				&& (!ft_strncmp(behind_str, ">>", 2)
					|| !ft_strncmp(behind_str, "<", 1)
					|| !ft_strncmp(behind_str, ">", 1)))
			return (checking_direction_expand(str, env));
		else if (!surounded_by(str, '\'')
				&& !surounded_by(str, '\"') && char_counter(str, ' '))
			return (recursive_why_not(str, env));
	}
	else
		if (!surounded_by(str, '\'')
				&& !surounded_by(str, '\"') && char_counter(str, ' '))
			return (recursive_untill_found(str, env));
	return (1);
}

void replace_spaces(char **ptr)
{
	int i;
	int h;

	i = 0; 
	h = ft_strlen (*ptr) -1;
	if ((*ptr[i]) == ' ')
	{
		(*ptr)[i] = '\1';
		i++;
	}
	if (h > 0 && (*ptr)[h] == ' ')
		(*ptr)[h] = '\1';
	while ((*ptr)[i])
	{
		if ((*ptr)[i] == ' ')
			(*ptr)[i] = '\4';
		i++;
	}
}

void no_extra_(char **ptr, char c)
{
	int i;
	int j;
	int k;
	char *re;

	if (!consecutive(*ptr, c))
		return ;
		re = ft_calloc (sizeof (char), ft_strlen (*ptr) + 1);
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
		free (*ptr);
		*ptr = ft_strdup (re);
		free (re);
}


void the_array_size_to_expand(t_expand *expand, char **ptr, char **env)
{
	expand->start = expand->i;
	while ((*ptr)[expand->i] && (ft_isalpha((*ptr)[expand->i+1])
				|| ft_isdigit((*ptr)[expand->i+1])
				|| (*ptr)[expand->i+1] == '_'))
		expand->i++;
	expand->end = expand->i;
	expand->tmp = take_copy((*ptr), expand->start + 1,
			expand->end);
	expand->k = 0;
	while (env[expand->k])
	{
		expand->h = ft_strlen(expand->tmp);
		if (!ft_strncmp(env[expand->k], expand->tmp, expand->h)
				&& env[expand->k][expand->h] == '=')
		{
			expand->k = ft_strlen (env[expand->k]);
			break;
		}
		expand->k++;
	}
	free (expand->tmp);
}

void expand_exit_stat_size(t_expand *expand, char **env)
{
	expand->tmp = ft_strdup ("?");
	expand->i++;
	expand->k = 0;
	expand->h = ft_strlen(expand->tmp);
	while (env[expand->k])
	{
		if (!ft_strncmp(expand->tmp, env[expand->k], expand->h)
			   	&& env[expand->k][expand->h] == '=')
		{
			expand->k = ft_strlen (env[expand->k]);
			break;
		}
		expand->k++;
	}
	free (expand->tmp);
}

void the_expander(t_expand *expand, char **ptr, char **env)
{
	expand->start = expand->i;
	while ((*ptr)[expand->i] && (ft_isalpha((*ptr)[expand->i+1])
			   	|| ft_isdigit((*ptr)[expand->i+1])
			   	|| (*ptr)[expand->i+1] == '_'))
		expand->i++;
	expand->end = expand->i;
	expand->tmp = take_copy((*ptr), expand->start + 1, expand->end);
	expand->k = -1;
	expand->h = ft_strlen(expand->tmp);
	while (env[++expand->k])
		if (!ft_strncmp(env[expand->k], expand->tmp, expand->h)
			   	&& env[expand->k][expand->h] == '=')
		{
			expand->tmp2 = take_copy(env[expand->k], expand->h + 1,
				   	ft_strlen(env[expand->k]));
			expand->k = 0;
			while (expand->tmp2[expand->k])
				expand->re[expand->j++] = expand->tmp2[expand->k++];
			free (expand->tmp2);
			break;
		}
	expand->j--;
	free (expand->tmp);
}

void expand_exit_stat_array(t_expand *expand, char **env)
{
	expand->tmp = ft_strdup ("?");
	expand->i++;
	expand->k = 0;
	expand->h = ft_strlen(expand->tmp);
	while (env[expand->k])
	{
		if (!ft_strncmp(expand->tmp, env[expand->k], expand->h)
			   	&& env[expand->k][expand->h] == '=')
		{
			expand->tmp2 = take_copy(env[expand->k], expand->h + 1,
				   	ft_strlen(env[expand->k]));
			expand->k = 0;
			while (expand->tmp2[expand->k])
				expand->re[expand->j++] = expand->tmp2[expand->k++];
			free (expand->tmp2);
			break;
		}
		expand->k++;
	}
	expand->j--;
	free (expand->tmp);
}

void time_to_expand(t_expand *expand, char **ptr, char **env)
{
	expand->re = malloc (sizeof (char) * (ft_strlen ((*ptr)) + expand->k + 1)
		   	* (char_counter((*ptr), '$')  + 1));
	expand->i = 0;
	expand->j = 0;
	while ((*ptr)[expand->i])
	{
		if ((*ptr)[expand->i] == '$' && (ft_isalpha((*ptr)[expand->i+1])
				   	|| ft_isdigit((*ptr)[expand->i+1])
				   	|| (*ptr)[expand->i+1] == '_'))
			the_expander(expand, ptr, env);
		else if ((*ptr)[expand->i] == '$' && (*ptr)[expand->i + 1] == '?')
			expand_exit_stat_array(expand, env);
		else
			expand->re[expand->j] = (*ptr)[expand->i];
		expand->j++;
		expand->i++;
	}
	expand->re[expand->j] = '\0';
}

void array_expander(char **ptr, char **env)
{
	t_expand expand;

	expand.i = 0;
	expand.k = 0;
	while ((*ptr)[expand.i])
	{
		if ((*ptr)[expand.i] == '$' && (ft_isalpha((*ptr)[expand.i+1])
				   	|| ft_isdigit((*ptr)[expand.i+1])
				   	|| (*ptr)[expand.i+1] == '_'))
			the_array_size_to_expand(&expand, ptr, env);
		else if ((*ptr)[expand.i] == '$' && (*ptr)[expand.i+1] == '?')
			expand_exit_stat_size(&expand, env);
		expand.i++;
	}
	time_to_expand(&expand, ptr, env);
	free (*ptr);
	*ptr = ft_strdup (expand.re);
	free (expand.re);
}

int len_from_env(char ***str_pro_max, char **env, int i, int *j)
{
	int start;
	int k;
	int h;
	int end;
	char *tmp;

	start = (*j);
	while ((*str_pro_max)[i][(*j)] &&
		   	(ft_isalpha((*str_pro_max)[i][(*j) + 1])
			 || ft_isdigit((*str_pro_max)[i][(*j) + 1])
			 || (*str_pro_max)[i][(*j) + 1] == '_'))
		(*j)++;
	end = (*j);
	tmp = take_copy((*str_pro_max)[i], start + 1, end);
	k = -1;
	h = ft_strlen(tmp);
	while (env[++k])
		if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
		{
			k = ft_strlen(env[k]);
			break;
		}
	free(tmp);	
	return (k);
}

int len_from_env_(char **env, int *j)
{
	char *tmp;
	int k;
	int h;

	tmp = ft_strdup ("?");
	(*j)++;
	k = 0;
	h = ft_strlen(tmp);
	while (env[k])
	{
		if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
		{
			k = ft_strlen (env[k]);
			break;
		}
		k++;
	}
	free (tmp);
	return (k);
}

int get_len_to_allocate(char ***str_pro_max, int i, char **env)
{
	int j;
	int k;

	k = 0;
	j = 0;
	while ((*str_pro_max)[i][j])
	{
		if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j+1] == '@'
				   	|| ft_isdigit((*str_pro_max)[i][j+1])))
			delete_them(&(*str_pro_max)[i], j, j + 1);
		if ((*str_pro_max)[i][j] == '$' && (ft_isalpha((*str_pro_max)[i][j + 1])
				   	|| (*str_pro_max)[i][j + 1] == '_'
				   	|| ft_isdigit((*str_pro_max)[i][j + 1])))
			k = len_from_env(&(*str_pro_max), env, i, &j);
		else if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j+1] == '?'))
			k = len_from_env_(env, &j);
		else
			j++;
		if (j >= (int)ft_strlen((*str_pro_max)[i]))
			break;
	}
	return (k + ft_strlen ((*str_pro_max)[i]));
}

void get_size_to_expand(char ***str, char ***str_pro_max, char **env)
{
	int i;

	i = 0;
	(*str) = ft_calloc (sizeof (char *) ,(ft_strcount(*str_pro_max) + 1));
	while ((*str_pro_max)[i])
	{
		(*str)[i] = ft_calloc (sizeof (char) ,(get_len_to_allocate(str_pro_max
						, i, env) + 1) * (char_counter((*str_pro_max)[i], '$') + 3));
		i++;
	}
}

char *take_variable_from_env(char **env, int k, char *str_pro_max, int h)
{
	char *tmp2;

	tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
	if (surounded_by(str_pro_max, '\"'))
		exchange(&tmp2, ' ', '\5');
	no_extra_(&tmp2, ' ');
	replace_spaces(&tmp2);
	tmp2 = ft_str_join(tmp2, "\2");
	return (tmp2);
}

void store_after_expand_var(char *tmp2, int *m, char **str)
{
	int k;

	k = 0;
	while (tmp2[k])
		(*str)[(*m)++] = tmp2[k++];
	free (tmp2);
}


void start_expanding(t_expand *expand, char ***str_pro_max, char **env)
{
	(*expand).start = (*expand).j;
	while ((*str_pro_max)[(*expand).i][(*expand).j]
			&& (ft_isalpha((*str_pro_max)[(*expand).i][(*expand).j + 1])
				|| ft_isdigit((*str_pro_max)[(*expand).i][(*expand).j + 1])
				|| (*str_pro_max)[(*expand).i][(*expand).j + 1] == '_'))
		(*expand).j++;
	(*expand).end = (*expand).j;
	(*expand).tmp = take_copy((*str_pro_max)[(*expand).i],
			(*expand).start + 1, (*expand).end); 
	(*expand).k = -1;
	while (env[++(*expand).k])
	{
		(*expand).h = ft_strlen((*expand).tmp);
		if (!ft_strncmp((*expand).tmp, env[(*expand).k],
				   	(*expand).h) && env[(*expand).k][(*expand).h] == '=')
		{
			(*expand).tmp2 = take_variable_from_env(env,
				   	(*expand).k, (*str_pro_max)[(*expand).i], (*expand).h);
			store_after_expand_var((*expand).tmp2, &(*expand).m,
				   	&((*expand).str)[(*expand).i]);
			break;
		}
	}
	(*expand).m--;
	free((*expand).tmp);
}

void expand_exit_stat(t_expand *expand, char **env)
{
	(*expand).tmp = ft_strdup ("?");
	(*expand).j++;
	(*expand).k = 0;
	(*expand).h = ft_strlen((*expand).tmp);
	while (env[(*expand).k])       	
	{
		if (!ft_strncmp((*expand).tmp, env[(*expand).k],
				   	(*expand).h) && env[(*expand).k][(*expand).h] == '=')
		{
			(*expand).tmp2 = take_copy(env[(*expand).k],
				   	(*expand).h + 1, ft_strlen(env[(*expand).k]));
			(*expand).k = 0;
			while ((*expand).tmp2[(*expand).k])
				(*expand).str[(*expand).i][(*expand).m++] =
				   	(*expand).tmp2[(*expand).k++];
			free ((*expand).tmp2);
			break;
		}
		(*expand).k++;
	}
	(*expand).m--;
	free ((*expand).tmp);
}

void fill_str(t_expand *expand, char ***str_pro_max, char **env)
{
	while ((*str_pro_max)[(*expand).i])
	{
		(*expand).j = 0;
		(*expand).m = 0;
		while ((*str_pro_max)[(*expand).i][(*expand).j])
		{
			if ((*str_pro_max)[(*expand).i][(*expand).j] == '$'
					&& (ft_isalpha((*str_pro_max)[(*expand).i][(*expand).j + 1]) 
						|| (*str_pro_max)[(*expand).i][(*expand).j + 1] == '_' 
						|| ft_isdigit((*str_pro_max)[(*expand).i][(*expand).j + 1])))
				start_expanding(&(*expand), str_pro_max, env);
			else if ((*str_pro_max)[(*expand).i][(*expand).j] == '$' && 
					((*str_pro_max)[(*expand).i][(*expand).j+1] == '?'))
				expand_exit_stat (&(*expand), env);
			else 
				(*expand).str[(*expand).i][(*expand).m] =
					(*str_pro_max)[(*expand).i][(*expand).j];
			(*expand).j++;
			(*expand).m++;
		}
		(*expand).i++;
	}
}

void expand_after_redirections(t_expand *expand, char ***str_pro_max, char **env)
{
	if (mega_counter((*str_pro_max), '\'') || mega_counter((*str_pro_max), '\"'))
		while ((*expand).j > 0)
		{
			(*expand).h = ft_strlen ((*str_pro_max)[(*expand).j]) - 1;
			if ((*expand).h >= 0 && (*str_pro_max)[(*expand).j][(*expand).h-1]
				   	== ' ')
				break;
			(*expand).j--;
		}
	if ((*expand).j >= 0 && (*expand).j != (*expand).i)
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
			   	(*str_pro_max)[(*expand).j], env);
	else if ((*expand).i > 0)
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
			   	(*str_pro_max)[(*expand).i - 1], env);
	else
		(*expand).to_expand = checking_direction((*str_pro_max)[(*expand).i],
			   	NULL, env);
}

void should_i_expand(t_expand *expand, char ***str_pro_max, char **env)
{
	(*expand).j = (*expand).i;
	expand_after_redirections(&(*expand), str_pro_max, env);
	if ((*expand).to_expand == 0)
		(*str_pro_max)[(*expand).i] = ft_str_join((*str_pro_max)[(*expand).i]  ,"\a");
	if (surounded_by((*str_pro_max)[(*expand).i], '\"') && expand->to_expand == 2)
		i_should_replace_them(&(*str_pro_max)[(*expand).i]);
	else if (!surounded_by((*str_pro_max)[(*expand).i], '\'') &&
		   	(*expand).to_expand == 1)
	{
		free ((*str_pro_max)[(*expand).i]);
		(*str_pro_max)[(*expand).i] = ft_strdup((*expand).str[(*expand).i]);
	}
}

void expand(char ***str_pro_max, char **env)
{
	t_expand expand;

	get_size_to_expand(&expand.str, str_pro_max, env);
	expand.i = 0;
	expand.j = 0;
	expand.start = 0;
	expand.end = 0;
	fill_str(&expand, str_pro_max, env);
	expand.i = -1;
	while ((*str_pro_max)[++expand.i])
		if (char_counter((*str_pro_max)[expand.i], '$'))
			should_i_expand(&expand, str_pro_max, env);
	free_double_array(expand.str);
}

void shlvl(char ***env, int c)
{
	int i;
	int h;
	char *tmp;
	char *tmp2;

	h = ft_strlen ("SHLVL=");
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "SHLVL=", h))
		{
			tmp = take_copy((*env)[i], h, ft_strlen((*env)[i]));
			tmp2 = ft_itoa(ft_atoi(tmp) + c);
			free (tmp);
			free ((*env)[i]);
			(*env)[i] = ft_strjoin("SHLVL=", tmp2);
			free (tmp2);
			return ;
		}
		i++;
	}
}

int error_detected(void)
{
	ft_printf ("bash: syntax error near unexpected token `|'\n");
	g_vars.g_exit_status = 2;
	return (0);
}

int fast_check(char *input)
{
	int i;

	i = 0;
	if (!input)
		return (0);
	while (input [i] && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (error_detected());
	while (input[i])
		i++;
	i--;
	while (i > 0 && input[i] == ' ')
		i--;
	if (i >= 0)
	{
		if (input[i] == '|')
			return (error_detected());
	}
	else 
		return (0);
	return (1);
}

void init_list(t_input **list, int count)
{
	(*list) = malloc (sizeof (t_input));
	(*list)->next = NULL;
	(*list)->cmd = NULL;
	(*list)->arg = ft_calloc (sizeof(char *), count + 1);
	(*list)->redirect = malloc (sizeof (t_redirection));
	(*list)->redirect->file_name = ft_calloc (sizeof(char *), count + 1);
	(*list)->redirect->type = ft_calloc (sizeof(char *), count + 1);
	(*list)->redirect->position = 0;
	(*list)->pipe = 0;
}

t_input *append(t_input *list, int count)
{
	while (list->next)
		list = list->next;
	init_list(&list->next, count);
	return (list);
}

int mega_counter(char **str, char c) // returns num of repetitions of a char in a double str
{
	int i;
	int re;

	i = 0;
	re = 0;
	while (str[i])
	{
		re += char_counter(str[i], c);
		i++;
	}
	return (re);
}


void exchange(char **ptr, char c, char b)
{
	int i;

	i = 0;
	while ((*ptr)[i])
	{
		if ((*ptr)[i] == c)
			(*ptr)[i] = b;
		i++;
	}
}

void ambiguous_starter_pack(char ***split)
{
	int i;
	int count;

	i = 0;
	while ((*split)[i])
	{
		count = char_counter((*split)[i], '\2');
		if ((count == 1 && (*split)[i][0] == '\1' && (*split)[i][1] == '\2' && ft_strlen ((*split)[i]) == 2))
			disable (&(*split)[i], '\1');
		if (char_counter((*split)[i], '\5'))
			exchange (&(*split)[i], '\5', ' ');
		i++;
	}
}

void list_append(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable (&split[i], '\2');
	if (char_counter(split[i+1], '\2'))
		disable (&split[i+1], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "2";
	if (split[i+1])
		(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
	(*list)->redirect->position++;
}
void list_heardoc(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable (&split[i], '\2');
	if (char_counter(split[i+1], '\2'))
		disable (&split[i+1], '\2');
	(*list)->redirect->type[(*list)->redirect->position] = "4";
	if (split[i+1])
		(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
	(*list)->redirect->position++;
}


void list_in(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable (&split[i], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "3";
	if (split[i+1])
		(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
	(*list)->redirect->position++;
}

void list_out(char **split, t_input **list, int i)
{
	if (char_counter(split[i], '\2'))
		disable (&split[i], '\2');
	no_surounded_anymore(&split[i + 1]);
	(*list)->redirect->type[(*list)->redirect->position] = "1";
	if (split[i+1])
		(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
	(*list)->redirect->position++;
}

void list_cmd(char **split, t_input **list, int i, int *m)
{
	int n;
	char **last_split;

	if (char_counter(split[i], '\2'))
		disable (&split[i], '\2');
	if (char_counter(split[i], '\1'))
		exchange(&split[i], '\1' , ' ');
	no_surounded_anymore(&split[i]);
	if (char_counter(split[i], '\4'))
	{
		last_split = ft_split(split[i], '\4');
		n = 0;
		(*list)->cmd = ft_strdup(last_split[n++]);
		while (last_split[n])
			(*list)->arg[(*m)++] = ft_strdup(last_split[n++]);
		free_double_array(last_split);
	}
	else
		(*list)->cmd = ft_strdup (split[i]);
}

void list_args(char **split, t_input **list, int i, int *m)
{
	int n;
	char **last_split;

	no_surounded_anymore(&split[i]);
	if (char_counter(split[i], '\4'))
	{
		last_split = ft_split(split[i], '\4');
		n = 0;
		while (last_split[n])
			(*list)->arg[(*m)++] = ft_strdup(last_split[n++]);
		free_double_array(last_split);
	}
	else
	{
		(*list)->arg[(*m)] = ft_strdup(split[i]);
		(*m)++;
	}
}

void list_details(char **split, t_input **list, int *i, int *m)
{
	int one_time;

	one_time = 1;
	while (split[(*i)])
	{
		if (!ft_strncmp(split[(*i)], ">>" , 2))
			list_append (split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], "<<" , 2))
			list_heardoc(split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], ">" , 2))
			list_out(split, list, (*i)++);
		else if (!ft_strncmp(split[(*i)], "<" , 1))
			list_in(split, list, (*i)++);
		else if (one_time == 1 && ft_strncmp(split [(*i)], "|", 2))
		{
			list_cmd(split, list, (*i), m);
			one_time = 0;
		}
		else if (!ft_strncmp(split [(*i)], "|", 1))
			break;
		else 
			list_args(split, list, (*i), m);
		(*i)++;
	}
}

void phil_the_list(t_input **list, char **split)
{
	int m;
	int count;
	int i;
	t_input *tmp;

	m = 0;
	ambiguous_starter_pack(&split);
	count = ft_strcount(split);
	tmp = *list;
	i = 0;
	while (split[i])
	{
		list_details(split, list, &i, &m);
		if (i >= count)
			break;
		if (!ft_strcmp(split [i], "|"))
		{
			(*list)->pipe = 1;
			append (*list, count);
			(*list) = (*list)->next;
			m = 0;
		}
		i++;
	}
	(*list) = tmp;
}

void check_ambiguous(t_input **list)
{
	int k;
	int count;
	int j;

	k = 0;
	while ((*list)->arg[k])
	{
		count = char_counter((*list)->arg[k], '\2');
		if ((count == 1 && ft_strlen ((*list)->arg[k]) <= 1) || (count == 1
				   	&& (*list)->arg[k][0] == '\1' && (*list)->arg[k][1]
				   	== '\2' && ft_strlen ((*list)->arg[k]) == 2))
		{
			j = k;
			while ((*list)->arg[j + 1])
			{
				free ((*list)->arg[j]);
				(*list)->arg[j] = ft_strdup ((*list)->arg[j + 1]);
				j++;
			}
			free ((*list)->arg[j]);
			(*list)->arg[j] = NULL;
			k = -1;
		}
		k++;
	}
}

void disable_some_checks(t_input **list)
{
	int k;

	k = 0;
	while ((*list)->arg[k])
	{
		if (char_counter((*list)->arg[k], '\2'))
			disable (&(*list)->arg[k], '\2');
		if (char_counter((*list)->arg[k], '\1'))
		{
			if ((*list)->arg[k][0] == '\1')
				disable(&(*list)->arg[k], '\1');
			else if ((*list)->arg[k][ft_strlen ((*list)->arg[k]) - 1] == '\1')
				disable (&(*list)->arg[k], '\1');
			else
				exchange(&(*list)->arg[k], '\1' , ' ');
		}
		k++;
	}
}

void phil_list(t_input **list, char **split)
{
	t_input *tmp;

	phil_the_list(list, split);
	tmp = *list;
	while (*list)
	{
		check_ambiguous(list);
		disable_some_checks(list);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

int ft_strmegacount(char **c)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			j++;
		}
		count += j;
		i++;
	}
	return (count);
}

t_input *work_time(char **split)
{
	t_input *list;

	init_list(&list, ft_strmegacount (split));
	phil_list(&list, split);
	return (list);
}

void free_list(t_input *list)
{
	t_input *tmp;

	tmp = list;
	while (tmp)
	{
		free(tmp->cmd);
		free_double_array (tmp->arg);
		free(tmp->redirect->type);
		free_double_array (tmp->redirect->file_name);
		free (tmp->redirect);
		list = list->next;
		free (tmp);
		tmp = list;
	}
}

int check_error(char **str, int i)
{
	int h;

	h = ft_strlen (str[i]);
	if (str[i + 1][0] == '|' && str[i][h - 1] == '>')
		return (i);
	if (str[i + 1][0] == '|' && str[i][h - 1] == '<')
		return (i);
	if (str[i + 1][0] == '>' && str[i][h - 1] == '<')
		return (i);
	if (str[i + 1][0] == '<' && str[i][h - 1] == '>')
		return (i);
	return (-1);
}

int last_check(char **str)
{
	int i;
	int h;

	i = -1;
	if (!str)
		return (-1);
	if (!str[i+1])
	{
		free_double_array(str);
		return (-2);
	}
	while (str[++i + 1])
		if (check_error(str, i) != -1)
			return (i);
	h = ft_strlen (str[i]);
	if (h > 0)
	{
		if (str[i][h - 1] == '>')
			return (i);
		if (str[i][h - 1] == '<')
			return (i);
	}
	return (-1);
}

// te perfect parsing does not exis ... 
char **parsing(char **input, char **env)
{
	char **new_str;
	char **str_pro_max; // the best one to use till moument

	new_str = split_without_weast (input);
	if (ft_strlen ((*input)) && !ft_strcount (new_str))
	{
		error_print ("bash: unexpected EOF while looking for matching", NULL);
		g_vars.g_exit_status = 2;
		free_double_array(new_str);
		return (NULL);
	}
	expand(&new_str, env);
	str_pro_max = ultra_split(new_str, input);
	free_double_array(new_str);
	the_joiner(&str_pro_max);
	no_etxra_qoutes(&str_pro_max);
	return (str_pro_max);
}


void sigint(int i)
{
	(void)i;
//	if (g_vars.pid[i] == 0)
//	{
//		ft_printf("\n");
//		rl_on_new_line();
//		rl_replace_line("", 1);
//		rl_redisplay();
//	}
//	else
//	{
//		while (g_vars.pid[i] != 0)
//		{
//			kill (g_vars.pid[i], SIGINT);
//			printf ("%d is dead now\n", g_vars.pid[i]);
//			g_vars.pid[i] = 0;
//			i++;
//		}
//		ft_bzero (g_vars.pid, PIPE_BUF);
//		g_vars.index = 0;
//	}
//	g_vars.g_exit_status = 130;
}

void sigquit(int i)
{
	while (g_vars.pid[i] != 0)
	{
		kill (g_vars.pid[i], SIGINT);
		printf ("%d is dead now\n", g_vars.pid[i]);
		g_vars.pid[i] = 0;
		i++;
	}
	ft_bzero (g_vars.pid, PIPE_BUF);
	g_vars.index = 0;
	ft_printf("Quit: 3\n");
}

void signals(int signum)
{
	int i;

 	i = 0;
 	if (signum == SIGINT)
		sigint(i);
 	else if (signum == SIGQUIT)
		sigquit(i);
 }

void re_split(char ***tmp, char **split, int *j)
{
	char **ptr;
	int k;

		if (char_counter ((*split), ' '))
		{
			ptr = ft_split((*split), ' ');
			k = 0;
			while (ptr[k])
				(*tmp)[(*j)++] = ptr[k++];
			free (ptr);
			if ((*j) > 0)
				(*j)--;
		}
		else
			(*tmp)[(*j)] = (*split);
}

void split_and_join(char ***split)
{
	int i;
	int j;
	char **tmp;

	if (!(*split))
		return ;
	tmp = ft_calloc (sizeof (char *) ,ft_strcount((*split)) + mega_counter(*split, ' ') + 2);
	i = 0;
	j = 0;
	while ((*split)[i])
	{
		re_split(&tmp, &(*split)[i], &j);
		j++;
		i++;
	}
	free (*split);
	*split = tmp;
}

void parse_it(char **copy, char ***env, char ***split)
{
	int check;

	if (char_counter((*copy), '\"') || char_counter((*copy), '\''))
		(*split) = parsing(&(*copy), *env);
	else
	{
		make_some_space(&(*copy));
		(*split) = ft_split ((*copy), ' ');
		expand (&(*split), *env);
		split_and_join(&(*split));
	}
	check = last_check((*split));
	if (check == -2)
		(*split) = NULL;
	if (check != -1 && (*split))
	{
		if (check  + 1 < ft_strcount((*split)))
			ft_printf ("bash: syntax error near unexpected token `%s'\n", (*split)[check + 1]);
		else
			error_print ("bash: syntax error near unexpected token `newline'", NULL);
		g_vars.g_exit_status = 2;
		free_double_array((*split));
		(*split) = NULL;
	}
}

void parse_phil_list_and_excute(char **copy, char ***env, char ***export)
{
	char **split;
	t_input *list;

	if (fast_check((*copy)))
	{
		parse_it(&(*copy), env, &split);
		ft_update_exit_status(env);
		if (split)
		{
			if (mega_counter(split, '*'))
				wildcard(&split);
			list = work_time(split);
			free_double_array(split);
			ft_execution(list, env, export);
			ft_update_exit_status(env);
			ft_update_last_command(env, list);
			free_list(list);
		}
	}
}

void minishell(char ***env, char ***export)
{
	char *input;
	char *copy;

	if (!g_vars.g_exit_status)
		input = readline("😄\033[0;32mbash-4.2\033[34m$▶️  \033[0m");
	else
		input = readline("😡\033[31mbash-4.2\033[34m$❌ \033[0m");
	if (input == NULL)
	{
		// ft_printf ("exit\n");
		free (input);
		exit (g_vars.g_exit_status);	
	}
	copy = ft_strdup(input);
	parse_phil_list_and_excute(&copy, env, export);
	free (copy);
	add_history(input);
	if (input && input[0] == 0)
		g_vars.g_exit_status = 0;
	free(input);
	ft_bzero (g_vars.pid, PIPE_BUF);
	g_vars.index = 0;
}

int main(int ac, char **av, char **envi)
{
	char **env;
	char **export;

	(void)ac;
	(void)av;
	env = fill(envi);
	env = ft_join_ptr_to_double_ptr(env, "?=0");
	shlvl(&env, 1);
	in_env(NULL, env, 1);
	export = fill(env);
	g_vars.g_exit_status = 0;
	g_vars.index = 0;
	// signal (SIGINT, signals);
	// signal (SIGQUIT, signals);
	while (1)
		minishell(&env, &export);
	shlvl(&env, -1);
	in_env(NULL, env, 1);
	free_double_array(env);
	free_double_array(export);
	exit (0);
}
