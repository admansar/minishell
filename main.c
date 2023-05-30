#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "minishell.h"

void make_some_space(char **str);
void	free_double_array(char **new_str);
void should_i_replace_them(char **input);
void printer(char **ptr);

//how many worlds before the letter indicated as the second char 
int ft_simularity_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
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
		re = malloc (sizeof (char) * ft_strlen(c));
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
		re[j] = '\0';
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


void d_delete(char **input) // d for double quotes
{	
	int i;
	int taken;
	int start;
	int end;
	float used;
	int len;

	i = 0;
	taken = 1;
	start = 0;
	end = 0;
	len = ft_strlen (*input) + 1;
	while ((*input)[i])
	{
		used = 0;
		if ((*input)[i] == '\"' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] == '\"' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start == end - 1)
		{
			if (start > 0)
				if ((*input)[start - 1] == ' ')
					used = 0.5;
			if (end < len)
				if ((*input)[end + 1] == ' ' || end + 1 == len)
					used += 0.5;
			if (used != 1)
			{
				delete_both(input, start, end, '\"');
				i = -1;
				start = 0;
				end = 0;
				taken = 1;
			}
		}
		i++;
	}
}

void s_delete(char **input) // s for single quotes
{	
	int i;
	int taken;
	int start;
	float used;
	int end;
	int len;

	i = 0;
	taken = 1;
	start = 0;
	end = 0;
	len = ft_strlen (*input) + 1;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] == '\'' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start == end - 1)
		{
			if (start > 0)
				if ((*input)[start - 1] == ' ')
					used = 0.5;
			if (end < len)
				if ((*input)[end + 1] == ' ' || end + 1 == len)
					used += 0.5;
			if (used != 1)
			{
				delete_both(input, start, end, '\'');
				i = -1;
				start = 0;
				end = 0;
				taken = 1;
			}
		}
		i++;
	}
}




//no need to the comment !!
//anyway this function delete the double qoutes that start and end with nothing inside
void delete_non_sense(char **input)
{
	(*input) = ft_str_join((*input), " ");
	d_delete(input);
	s_delete(input);
}

//better for cheking errors the advantage of it that i split the double quote without waisting the double quotes
char **split_without_weast(char **input) 
{
	int i;
	int j;
	int k;
	int taken;
	int start;
	int end;
	char **new_str;

	new_str = malloc (sizeof (char *) * ft_strlen((*input)));
	start = 0;
	end = 0;
	taken = 1;
	j = 0;
	i = 0;
	while ((*input)[i])
	{
		if (((*input)[i] == '\"'||(*input)[i] == '\'') && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if (taken == 1) 
		{
			new_str[j] = ft_calloc (sizeof (char), (ft_strlen((*input)) + 1));
			k = 0;
			while ((*input)[i] && (*input)[i] != '\''  && (*input)[i] != '\"')
			{ 
				new_str[j][k] = (*input)[i];
				k++;
				i++;
			}
			new_str[j][k] = '\0';
			should_i_replace_them(&new_str[j]);
			make_some_space(&new_str[j]);
			j++;
			i--;
		}
		else if (((*input)[i] == '\"'||(*input)[i] == '\'') && taken == 0 && (*input)[start] == ((*input)[i]))
		{
			end = i;
			if ((*input)[i + 1] == ' ')
				end = ++i;
			taken = 1;
		}
		if (start < end)
		{
			new_str[j++] = take_copy((*input), start, end);
			if (!surounded_by(new_str[j - 1], '\"'))
				should_i_replace_them(&new_str[j - 1]);
			start = end;
		}
		i++;
	}
	new_str[j] = NULL;
	if (start > end)
	{
		free_double_array(new_str);
		new_str = NULL;
		return (NULL);
	}
	return (new_str);
}


//search if a letter 'c' is inside a single quotes 
int insider(char **input, char c)
{
	int i;
	int k;
	int taken;
	int start;
	int end;
	char *str;

	start = 0;
	k = 0;
	end = 0;
	taken = 1;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] == '\'' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start < end)
		{
			str = take_copy((*input), start, end);
			while (str[k])
			{
				if (str[k] == c)
				{
					free(str);
					return (1);
				}
				k++;
			}
			free (str);
			str = NULL;
			start = end;
		}
		i++;
	}
	return (0);
}


// in some cases the single quote act exactly like double quotes ... then should i replace them in that case ?
void should_i_replace_them(char **input)
{
	int i;
	int taken;
	int start;
	int end;
	char *str;

	start = 0;
	end = 0;
	taken = 1;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] == '\'' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start < end)
		{
			str = take_copy((*input), start, end);
			if (!char_counter(str, '\"') && !char_counter(str, '$'))
			{
				(*input)[start] = '\"';
				(*input)[end] = '\"';
			}
			free (str);
			str = NULL;
			start = end;
		}
		i++;
	}
}

// i mean the name is really clear
void i_should_replace_them(char **input)
{
	int i;
	int taken;
	int start;
	int end;
	char *str;

	start = 0;
	end = 0;
	taken = 1;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] == '\'' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start < end)
		{
			str = take_copy((*input), start, end);
			if (!char_counter(str, '\"'))
			{
				(*input)[start] = '\"';
				(*input)[end] = '\"';
			}
			free (str);
			str = NULL;
			start = end;
		}
		i++;
	}
}


//to suround a string by the quotes
void rebuild_using(char **ptr, char c)
{
	char *tmp;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	tmp = ft_calloc (sizeof(char), (2 + ft_strlen(*ptr)));
	tmp[j++] = c;
	while ((*ptr)[i])
	{
		if (k == 2 && (*ptr)[i] == ' ')
		{
			tmp[j++] = c;
			tmp[j++] = ' ';
			i++;
		}
		if ((*ptr)[i] != c)
		{
			tmp[j] = (*ptr)[i];
			j++;
		}
		else 
			k++;
		i++;
	}
	if (char_counter(tmp, c) != 2)
		tmp[j++] = c;
	tmp[j] = '\0';
	free (*ptr);
	*ptr = malloc (sizeof (char) * (ft_strlen(tmp) + 1));
	ft_strlcpy(*ptr, tmp, ft_strlen(tmp) + 1);
	free(tmp);
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

//the best split for the project 
char **ultra_split(char **new_str , char **input)
{
	char **split;
	char **str_pro_max;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	str_pro_max = ft_calloc(sizeof(char *), ft_strlen((*input)));
	while (new_str[i])
	{
		if (!surounded_by(new_str[i], '\"') && char_counter(new_str[i], ' ')  && !surounded_by(new_str[i], '\''))
		{
			make_some_space(&(new_str)[i]);
			split = my_spliter(new_str[i], 0, 0, 0);
			if (new_str[i][ft_strlen(new_str[i]) - 1] == ' ')
				split[ft_strcount(split) - 1] = ft_str_join(split[ft_strcount(split) - 1], " ");
			j = 0;
			while (split[j])
			{
				str_pro_max [k] = ft_strdup(split[j]);
				j++;
				k++;
			}
			free_double_array(split);
		}
		else
		{
			str_pro_max[k] = ft_strdup(new_str[i]);		
			k++;
		}
		i++;
	}
	return (str_pro_max);
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
				j = i + 1;
				while ((*str_pro_max)[j + 1])
				{
					free ((*str_pro_max)[j]);
					(*str_pro_max)[j] = ft_strdup((*str_pro_max)[j + 1]);
					j++;
				}
				free((*str_pro_max)[j]);
				(*str_pro_max)[j] = NULL;
				i = -1;
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

//delete the usless iner things
void delete_them_inside(char **ptr, char c)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		h;
	int		number_of_char;

	i = 0;
	j = 0;
	k = 0;
	h = ft_strlen((*ptr));
	number_of_char = char_counter(*ptr, c);
	tmp = ft_calloc (sizeof(char), (ft_strlen(*ptr) + 3));
	tmp[j++] = c;
	while ((*ptr)[i])
	{
		if (k == number_of_char && (*ptr)[i] == dual(c))
		{
			tmp[j++] = c;
			k = number_of_char + 1;
		}
		if (k == number_of_char && (*ptr)[i] == ' ')
		{
			tmp[j++] = c;
			tmp[j++] = ' ';
			i++;
			if (i == h)
				break;
		}
		if ((*ptr)[i] != c)
		{
			tmp[j] = (*ptr)[i];
			j++;
		}
		else  
			k++;
		i++;
	}
	if (char_counter(tmp, c) != 2)
		tmp[j++] = c;
	tmp[j] = '\0';
	free (*ptr);
	*ptr = malloc (sizeof (char) * (ft_strlen(tmp) + 1));
	ft_strlcpy(*ptr, tmp, ft_strlen(tmp) + 1);
	free(tmp);
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


// making space to let the "rederections" easy to detect inside by the ultra_split 
void make_some_space(char **str) 
{
	char *tmp;
	int j;
	int i;

	j = 0;  
	i = 0;


	if ((char_counter((*str),'>')) || (char_counter((*str),'<')) || (char_counter((*str),'|')))
	{
		tmp = ft_calloc(sizeof(char), ft_strlen((*str)) + (char_counter((*str),'>') * 2) + (char_counter((*str),'<') * 2) +  (char_counter((*str),'|') * 2) + 1);
		while ((*str)[i])
		{

			if ((*str)[i] == '>' && (*str)[i + 1] == '>')
			{
				tmp[j++] = ' ';
				tmp[j++] = '>';
				tmp[j++] = '>';
				tmp[j++] = ' ';
				i+=2;
			}
			else if ((*str)[i] == '>')
			{
				tmp[j++] = ' ';
				tmp[j++] = '>';
				tmp[j++] = ' ';
				i++;
			}
			else if ((*str)[i] == '|')
			{
				tmp[j++] = ' ';
				tmp[j++] = '|';
				tmp[j++] = ' ';
				i++;
			}
			else if ((*str)[i] == '<' && (*str)[i + 1] == '<')
			{
				tmp[j++] = ' ';
				tmp[j++] = '<';
				tmp[j++] = '<';
				tmp[j++] = ' ';
				i+=2;
			}
			else if ((*str)[i] == '<')
			{
				tmp[j++] = ' ';
				tmp[j++] = '<';
				tmp[j++] = ' ';
				i++;
			}
			else 
			{
		//		if ((*str)[i] == '\1')
		//		{
		//			i++;
		//			while ((*str)[i] != 0 && (*str[i] != '\1'))
		//				tmp[j++] = (*str)[i++];
		//			if ((*str)[i] != '\0')
		//				i++;
		//		}
		//		else
					tmp[j++] = (*str)[i++];
			}
		}
		free((*str));
		(*str) = ft_strdup(tmp);
		free (tmp);
	}
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

int in_env(char *ptr, char **env, int flag) //this function cheeck if a pointer ptr is in the envirement and also save the env , you can  change it by sending 1 as a flag , it returns in which place the ptr is, in case the ptr its  exists in the env else it return -1
	// new feature added send flag 2 to print the current env !! have fun
{
	static char **the_env;
	int k;
	int h;

	if (flag == 1)
	{
		if (!the_env)
		{
			the_env = fill(env);
		}
		else if (env)
		{
			free_double_array(the_env);
			the_env = fill(env);
		}
		return (-2);
	}
	if (flag == 2)
	{
		k = 0;
		while (the_env[k])
			printf ("%s\n", the_env[k++]);
		return (-3);
	}
	k = 0;
	while (the_env[k])
	{
		h = ft_strlen (ptr);
		if (!ft_strncmp(the_env[k], ptr, h) && the_env[k][h] == '=')
			return (k);
		k++;
	}
	return (-1);

}

int	checking_direction(char *str, char *behind_str, char **env) //this function take a look the expand to make it more exact ...
{
	char *tmp;
	int end;
	int i;
	char **split;

	end = 1;
	if (behind_str)
	{
		if (!surounded_by(str, '\'') && /* !char_counter(str, ' ') && */ (!ft_strncmp(behind_str + ft_simularity_len(behind_str, '<'), "<<", 2)))
			return (2);
		else if (!surounded_by(str, '\'') && !surounded_by(str, '\"') && !char_counter(str, ' ') && (!ft_strncmp(behind_str, ">>", 2) || !ft_strncmp(behind_str, "<", 1) || !ft_strncmp(behind_str, ">", 1)))
		{
			end = ft_simularity_len(str, '$');

			while (str[end + 1] && (ft_isalpha(str[end + 1]) || ft_isdigit((str[end + 1])) || (str[end + 1] == '_')))
				end++;

			tmp = take_copy(str, ft_simularity_len(str, '$') + 1, end);
			i = in_env(tmp, NULL, 0);
			if (i >= 0)
			{
				if (!char_counter(env[i], ' '))
				{
					free (tmp);
					return (1);
				}
				// else
				// {
					// free (tmp);
					// return (0);
				// }
			}
			else
			{
				free (tmp);
				return (0);
			}
		}
		else if (!surounded_by(str, '\'') && !surounded_by(str, '\"') && char_counter(str, ' '))
		{
			split = ft_split(str, ' ');
			i = -1;
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
	}
	else
	{
		if (!surounded_by(str, '\'') && !surounded_by(str, '\"') && char_counter(str, ' '))
		{
			split = ft_split(str, ' ');
			i = -1;		
			while (split[++i])
				if (char_counter(split[i], '$'))
				{
					if (i > 0)
					{
						end = checking_direction(split[i], split[i - 1], env);
						break;
					}	
				}
			free_double_array(split);
			return (end);
		}
	}
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

void no_extra_space(char **ptr)
{
	int i;
	int j;
	int k;
	char *re;
	int len;

	len = ft_strlen (*ptr) + 1;
	re = ft_calloc (sizeof (char), len);
	i = 0;
	j = 0;
	while ((*ptr)[i])
	{
		k = 0;
		while ((*ptr)[i] == ' ' && (*ptr)[i])
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

void array_expander(char **ptr, char **env)
{
	int i;
	int h;
	int j;
	int k;
	int start;
	int end;
	char *str;
	char *tmp;
	char *tmp2;
	char *re;

	i = 0;
	str = *ptr;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i+1]) || ft_isdigit(str[i+1]) || str[i+1] == '_'))
		{
			start = i;
			while (str[i] && (ft_isalpha(str[i+1]) || ft_isdigit(str[i+1]) || str[i+1] == '_'))
				i++;
			end = i;
			tmp = take_copy(str, start + 1, end);
			k = 0;
			while (env[k])
			{
				h = ft_strlen(env[k]);
				if (!ft_strncmp(env[k], tmp, h) && env[k][h] == '=')
				{
					k = ft_strlen (env[k]);
					break;
				}
					k++;
			}
			free (tmp);
		}
		else if (str[i] == '$' && str[i+1] == '?')
		{
				tmp = ft_strdup ("?");
				i++;
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
			}
		i++;
	}
	re = malloc (sizeof (char) * (ft_strlen (str) + k + 1) * (char_counter(str, '$')  + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i+1]) || ft_isdigit(str[i+1]) || str[i+1] == '_'))
		{
			start = i;
			while (str[i] && (ft_isalpha(str[i+1]) || ft_isdigit(str[i+1]) || str[i+1] == '_'))
				i++;
			end = i;
			tmp = take_copy(str, start + 1, end);
			k = 0;
			while (env[k])
			{
				h = ft_strlen(env[k]);
				if (!ft_strncmp(env[k], tmp, h) && env[k][h] == '=')
				{
					tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
					k = 0;
				   while (tmp2[k])
					   re[j++] = tmp2[k++];
				   free (tmp2);
					break;
				}
					k++;
			}
			j--;
			free (tmp);
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
				tmp = ft_strdup ("?");
				i++;
				k = 0;
				h = ft_strlen(tmp);
				while (env[k])
				{
					if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
					{
						tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
						k = 0;
						while (tmp2[k])
							re[j++] = tmp2[k++];
						free (tmp2);
						break;
					}
					k++;
				}
				j--;
				free (tmp);
		}
		else
			re[j] = str[i];
		j++;
		i++;
	}
	re[j] = '\0';
	free (*ptr);
	*ptr = ft_strdup (re);
}

void expand(char ***str_pro_max, char **env)
{
	int i;
	int k;
	int h;
	int j;
	int m;
	int start;
	int end;
	char *tmp;
	char *tmp2;
	char **str;
	int to_expand;

	i = 0;
	j = 0;
	start = 0;
	end = 0;

	str = ft_calloc (sizeof (char *) ,(ft_strcount(*str_pro_max) + 1));
	while ((*str_pro_max)[i])
	{
		j = 0;
		k = 0;
		start = 0;
		end = 0;
		while ((*str_pro_max)[i][j])
		{
			if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j+1] == '@' || ft_isdigit((*str_pro_max)[i][j+1])))
			{
				delete_them(&(*str_pro_max)[i], j, j + 1);
			}
			if ((*str_pro_max)[i][j] == '$' && (ft_isalpha((*str_pro_max)[i][j + 1]) || (*str_pro_max)[i][j + 1] == '_' || ft_isdigit((*str_pro_max)[i][j + 1])))
			{
				start = j;
				while ((*str_pro_max)[i][j] && (ft_isalpha((*str_pro_max)[i][j + 1]) || ft_isdigit((*str_pro_max)[i][j + 1]) || (*str_pro_max)[i][j + 1] == '_'))
					j++;
				end = j;
				tmp = take_copy((*str_pro_max)[i], start + 1, end);
				k = 0;
				while (env[k])
				{
					h = ft_strlen(tmp);
					if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
					{
						k = ft_strlen(env[k]);
						break;
					}
					k++;
				}
				free(tmp);	
				if (j >= (int)ft_strlen((*str_pro_max)[i]))
					break;
			}
			else if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j+1] == '?'))
			{
				tmp = ft_strdup ("?");
				j++;
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
				if (j >= (int)ft_strlen((*str_pro_max)[i]))
					break;
				free (tmp);
			}
			else
				j++;
		}
		str[i] = ft_calloc (sizeof (char) ,(ft_strlen ((*str_pro_max)[i]) + k + 1) * (char_counter((*str_pro_max)[i], '$') + 3));
		i++;
	}
	i = 0;
	j = 0;
	start = 0;
	end = 0;
	while ((*str_pro_max)[i])
	{
		j = 0;
		m = 0;
		while ((*str_pro_max)[i][j])
		{
			if ((*str_pro_max)[i][j] == '$' && ( ft_isalpha((*str_pro_max)[i][j + 1]) 
						|| (*str_pro_max)[i][j + 1] == '_' 
						|| ft_isdigit((*str_pro_max)[i][j + 1])))
			{
				start = j;
				while ((*str_pro_max)[i][j] && (ft_isalpha((*str_pro_max)[i][j + 1])
							|| ft_isdigit((*str_pro_max)[i][j + 1])
							|| (*str_pro_max)[i][j + 1] == '_'))
					j++;
				end = j;
				tmp = take_copy((*str_pro_max)[i], start + 1, end); 
				k = 0;
				while (env[k])
				{
					h = ft_strlen(tmp);
					if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
					{
						tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
						no_extra_space(&tmp2);
						replace_spaces(&tmp2);
						tmp2 = ft_str_join(tmp2, "\2");
						//		free (tmp);
						//		tmp = ft_strjoin ("\1", tmp2);
						//		free (tmp2);
						//		tmp2 = ft_str_join (tmp, "\1");
						//		tmp = NULL;
						k = 0;
						while (tmp2[k])
							str[i][m++] = tmp2[k++];
						free (tmp2);
						break;
					}
					k++;
				}
				m--;
				free(tmp);
			}
			else if ((*str_pro_max)[i][j] == '$' && ((*str_pro_max)[i][j+1] == '?'))
			{
				tmp = ft_strdup ("?");
				j++;
				k = 0;
				h = ft_strlen(tmp);
				while (env[k])
				{
					if (!ft_strncmp(tmp, env[k], h) && env[k][h] == '=')
					{
						tmp2 = take_copy(env[k], h + 1, ft_strlen(env[k]));
						k = 0;
						while (tmp2[k])
							str[i][m++] = tmp2[k++];
						free (tmp2);
						break;
					}
					k++;
				}
				m--;
				free (tmp);
			}
			else 
				str[i][m] = (*str_pro_max)[i][j];
			j++;
			m++;
		}
		i++;
	}
	i = 0;
	while ((*str_pro_max)[i])
	{
		if (char_counter((*str_pro_max)[i], '$'))
		{
			j = i;
			while (j > 0)
			{
				h = ft_strlen ((*str_pro_max)[j]) - 1;
				if (h >= 0 && (*str_pro_max)[j][h] == ' ')
					break;
				j--;
			}
			if (j >= 0 && j != i)
				to_expand = checking_direction((*str_pro_max)[i], (*str_pro_max)[j], env);
			else if (i > 0)
				to_expand = checking_direction((*str_pro_max)[i], (*str_pro_max)[i - 1], env);
			else
				to_expand = checking_direction((*str_pro_max)[i], NULL, env);
			if (to_expand == 0)
			{
				// (*str_pro_max)[i] = ft_str_join((*str_pro_max)[i]  ,"\a"); // if you see a '\a' it means only and one thing that this is a error "ambiguous redirect in this case", you also hear a 'ding' sound on it 
			}
			if (surounded_by((*str_pro_max)[i], '\"') && to_expand == 2)
			{
				i_should_replace_them(&(*str_pro_max)[i]);
			}
			else if (!surounded_by((*str_pro_max)[i], '\'') && to_expand == 1)
			{
				free ((*str_pro_max)[i]);
				(*str_pro_max)[i] = ft_strdup(str[i]);
			}
			//		else
			//			i_should_replace_them(&(*str_pro_max)[i]);
		}
		i++;
	}
	free_double_array(str);
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

int fast_check(char *input)
{
	int i;

	i = 0;
	if (!input)
		return (0);
	while (input [i] && input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		ft_printf ("bash: syntax error near unexpected token `|'\n");
		g_vars.g_exit_status = 2;
		return (0);
	}
	while (input[i])
		i++;
	i--;
	while (i > 0 && input[i] == ' ')
		i--;
	if (i >= 0)
	{
		if (input[i] == '|')
		{
			ft_printf ("bash: syntax error near unexpected token `|'\n");
			g_vars.g_exit_status = 2;
			return (0);
		}
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

void phil_list(t_input **list, char **split)
{
	int i;
	int m;
	int n;
	int one_time;
	int count;
	t_input *tmp;
	int j;
	char **last_split;

	i = 0;
	m = 0;
	one_time = 0;
	tmp = *list;

	// printer (split);
while (split[i])
{
	count = char_counter(split[i], '\2');
	if ((count == 1 && ft_strlen (split[i]) <= 1) || (count == 1 && split[i][0] == '\1' && split[i][1] == '\2' && ft_strlen (split[i]) == 2))
	{
		j = i;
		while (split[j + 1])
		{
			free (split[j]);
			split[j] = ft_strdup (split[j + 1]);
			j++;
		}
		free (split[j]);
		split[j] = NULL;
		i = -1;
	}
	i++;
}
	// printer (split);
	i = 0;
	// while (split[i])
	// {
	//	if (char_counter(split[i], '\1')) // '\1' ida kan space only f lwl ola f lakher ida kan mexpandi 
	//	{
	//		j = 0;
	//		while (split[i][j])
	//		{
	//			if (split[i][j] == '\1')
	//				split[i][j] = ' ';
	//			j++;
	//		}
	//	}
		//	disable (&split[i], '\1');
	//	if (char_counter(split[i], '\4')) // '\4' katkon f west ida kan mexpandi
	//	{
	//		j = 0;
	//		while (split[i][j])
	//		{
	//			if (split[i][j] == '\4')
	//				split[i][j] = ' ';
	//			j++;
	//		}
	//	}
	// 	i++;
	// }
	count = ft_strcount(split);
	i = 0;
	while (split[i])
	{
		one_time = 1; 
		while (split[i])
		{
			if (!ft_strncmp(split[i], ">>" , 2))
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
				if (char_counter(split[i+1], '\2'))
					disable (&split[i+1], '\2');
				no_surounded_anymore(&split[i + 1]);
				(*list)->redirect->type[(*list)->redirect->position] = "2";
				if (split[i+1])
				(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
				//	  printf ("file name : %s taked the pos num : %d and type is %s\n", (*list)->redirect->file_name[(*list)->redirect->position], (*list)->redirect->position + 1 , (*list)->redirect->type[(*list)->redirect->position]);
				(*list)->redirect->position++;
			}
			else if (!ft_strncmp(split[i], "<<" , 2))
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
				if (char_counter(split[i+1], '\2'))
					disable (&split[i+1], '\2');
				(*list)->redirect->type[(*list)->redirect->position] = "4";
				if (split[i+1])
				(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
				//	  printf ("file name : %s taked the pos num : %d and type is %s\n", (*list)->redirect->file_name[(*list)->redirect->position], (*list)->redirect->position + 1 , (*list)->redirect->type[(*list)->redirect->position]);
				(*list)->redirect->position++;
			}
			else if (!ft_strncmp(split[i], ">" , 2))
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
				// if (char_counter(split[i+1], '\2'))
					// disable (&split[i+1], '\2');
				no_surounded_anymore(&split[i + 1]);
				(*list)->redirect->type[(*list)->redirect->position] = "1";
				if (split[i+1])
				(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
				//	  printf ("file name : %s taked the pos num : %d and type is %s\n", (*list)->redirect->file_name[(*list)->redirect->position], (*list)->redirect->position + 1 , (*list)->redirect->type[(*list)->redirect->position]);
				(*list)->redirect->position++;
			}
			else if (!ft_strncmp(split[i], "<" , 1))
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
					// if (char_counter(split[i+1], '\2'))
					// disable (&split[i+1], '\2');
				no_surounded_anymore(&split[i + 1]);
				(*list)->redirect->type[(*list)->redirect->position] = "3";
				if (split[i+1])
					(*list)->redirect->file_name[(*list)->redirect->position] = ft_strdup (split[++i]);
				//	  printf ("file name : %s taked the pos num : %d and type is %s\n", (*list)->redirect->file_name[(*list)->redirect->position], (*list)->redirect->position + 1 , (*list)->redirect->type[(*list)->redirect->position]);
				(*list)->redirect->position++;
			}
			else if (one_time == 1 && ft_strncmp(split [i], "|", 2))
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
				if (char_counter(split[i], '\1'))
					exchange(&split[i], '\1' , ' ');
				no_surounded_anymore(&split[i]);
		//			disable (&split[i], '\1');
				if (char_counter(split[i], '\4'))
				{
					last_split = ft_split(split[i], '\4');
					n = 0;
					(*list)->cmd = ft_strdup(last_split[n++]);
					while (last_split[n])
						(*list)->arg[m++] = ft_strdup(last_split[n++]);
					free_double_array(last_split);
				}
				else
				(*list)->cmd = ft_strdup (split[i]);
				//	  printf ("cmd : %s\n", (*list)->cmd);
				one_time = 0;
			}
			else if (!ft_strncmp(split [i], "|", 1))
				break;
			else
			{
				if (char_counter(split[i], '\2'))
					disable (&split[i], '\2');
				if (char_counter(split[i], '\1'))
				{
					if (split[i][0] == '\1')
						disable(&split[i], '\1');
					else if (split[i][ft_strlen (split[i]) - 1] == '\1')
						disable (&split[i], '\1');
					else
						exchange(&split[i], '\1' , ' ');
				}
				no_surounded_anymore(&split[i]);
				//		if (char_counter(split[i], '\1'))
				//			disable (&split[i], '\1');
				if (char_counter(split[i], '\4'))
				{
					last_split = ft_split(split[i], '\4');
					n = 0;
					while (last_split[n])
						(*list)->arg[m++] = ft_strdup(last_split[n++]);
					free_double_array(last_split);
				}
				else
				{
					(*list)->arg[m] = ft_strdup(split[i]);
					// printf ("arg : %s\n", (*list)->arg[m]);
					m++;
				}
			}
			i++;
		}
		if (i >= count)
			break;
		if (!ft_strcmp(split [i], "|"))
		{
			(*list)->pipe = 1;
			append (*list, count);
			(*list) = (*list)->next;
			//		printf ("-->pipe\n");
			m = 0;
		}
		i++;
	}
	// printer ((*list)->arg);
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

int last_check(char **str)
{
	int i;
	int h;

	i = 0;
	if (!str)
		return (-1);
	if (!str[i])
	{
		free_double_array(str);
		return (-2);
	}
	while (str[i + 1])
	{
		h = ft_strlen (str[i]);
		if (str[i + 1][0] == '|' && str[i][h - 1] == '>')
			return (i);
		if (str[i + 1][0] == '|' && str[i][h - 1] == '<')
			return (i);
		if (str[i + 1][0] == '>' && str[i][h - 1] == '<')
			return (i);
		if (str[i + 1][0] == '<' && str[i][h - 1] == '>')
			return (i);
		i++;
	}
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
	// printer(new_str);
	str_pro_max = ultra_split(new_str, input);
	free_double_array(new_str);
	the_joiner(&str_pro_max);
	no_etxra_qoutes(&str_pro_max);
	// ft_wildcard(&str_pro_max);
	// printer(str_pro_max);
	// printf("\n------------------\n");
	return (str_pro_max);
}


// void signals(int signum)
// {
// 	int i;

// 	i = 0;
// 	if (signum == SIGINT)
// 	{
// 		if (g_vars.pid[i] == 0)
// 		{
// 			ft_printf("\n");
// 			rl_on_new_line();
// 			rl_replace_line("", 1);
// 			rl_redisplay();
// 		}
// 		else
// 		{
// 			while (g_vars.pid[i] != 0)
// 			{
// 				kill (g_vars.pid[i], SIGINT);
// 				printf ("%d is dead now\n", g_vars.pid[i]);
// 				g_vars.pid[i] = 0;
// 				i++;
// 			}
// 			ft_bzero (g_vars.pid, PIPE_BUF);
// 			g_vars.index = 0;
// 		}
// 		g_vars.g_exit_status = 130;
// 	}
// 	else if (signum == SIGQUIT)
// 	{
// 		while (g_vars.pid[i] != 0)
// 		{
// 			kill (g_vars.pid[i], SIGINT);
// 			printf ("%d is dead now\n", g_vars.pid[i]);
// 			g_vars.pid[i] = 0;
// 			i++;
// 		}
// 		ft_bzero (g_vars.pid, PIPE_BUF);
// 		g_vars.index = 0;
// 		ft_printf("Quit: 3\n");
// 	}
// }

void split_and_join(char ***split)
{
	int i;
	int j;
	int k;
	char **ptr;
	char **tmp;
	if (!(*split))
		return ;
	tmp = ft_calloc (sizeof (char *) ,ft_strcount((*split)) + mega_counter(*split, ' ') + 2);
	i = 0;
	j = 0;
	while ((*split)[i])
	{
		if (char_counter ((*split)[i], ' '))
		{
			ptr = ft_split((*split)[i], ' ');
			k = 0;
			while (ptr[k])
				tmp[j++] = ptr[k++];
			free (ptr);
			if (j > 0)
				j--;
		}
		else
			tmp[j] = (*split)[i];
		j++;
		i++;
	}
	free (*split);
	*split = tmp;
}



int main(int ac, char **av, char **envi)
{
	char *input;
	char *copy;
	char **split;
	char **env;
	t_input *list;
	int check;
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
	//	ft_printf("\033[37mThe default interactive shell is now zsh.\nTo update your account to use zsh, please run chsh -s /bin/zsh.\n\033[0m");
	while (1)
	{
		if (!g_vars.g_exit_status)
			input = readline("\033[0;32mbash-4.2\033[34m$ \033[0m");
		else
			input = readline("\033[31mbash-4.2\033[34m$ \033[0m");
		if (input == NULL)
		{
			// ft_printf ("exit\n");
			free (input);
			exit (g_vars.g_exit_status);	
		}
		copy = ft_strdup(input);
		if (fast_check(copy))
		{
			if (char_counter(copy, '\"') || char_counter(copy, '\''))
			{
				split = parsing(&copy, env);
				ft_wildcard(&split);
				printer(split);
				printf("\n------------------\n");
			}
			else
			{
				make_some_space(&copy);
				split = ft_split (copy, ' ');
				expand (&split, env);
				printer(split);
				printf("\n------------------\n");
				check = 0;
				split_and_join(&split);
			}
				// printer(split);
			check = last_check(split);
			if (check == -2)
				split = NULL;
			if (check != -1 && split)
			{
				if (check  + 1 < ft_strcount(split))
					ft_printf ("bash: syntax error near unexpected token `%s'\n", split[check + 1]);
				else
					error_print ("bash: syntax error near unexpected token `newline'", NULL);
				g_vars.g_exit_status = 2;
				free_double_array(split);
				split = NULL;
			}
			ft_update_exit_status(&env);
			if (split)
			{
				list = work_time(split);
				free_double_array(split);
				ft_execution(list, &env, &export);
				ft_update_exit_status(&env);
				ft_update_last_command(&env, list);
				// printer(env);
				free_list(list);
			}
		}
				// while (1);
		free (copy);
		add_history(input);
		free(input);
		ft_bzero (g_vars.pid, PIPE_BUF);
		g_vars.index = 0;
	}
	shlvl(&env, -1);
	in_env(NULL, env, 1);
	free_double_array(env);
	free_double_array(export);
	exit (0);
}
