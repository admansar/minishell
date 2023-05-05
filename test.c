#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include "libft/ft_printf.h"

void make_some_space(char **str);
void	free_double_array(char **new_str);
void should_i_replace_them(char **input);
//how many worlds before the letter indicated as the second char 
int ft_simularity_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
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
			new_str[j] = ft_calloc (sizeof (char) , (ft_strlen((*input)) + 1));
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
		if ((*str_pro_max)[i][h] != ' ' && !k && (*str_pro_max)[i + 1][0] != '>' && (*str_pro_max)[i + 1][0] != '<')
		{
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
		printf ("%s$\n", ptr[i++]);
	printf ("-------%d\n", ft_strcount(ptr));
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
	tmp = ft_calloc (sizeof(char), (ft_strlen(*ptr) + 2));
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
				tmp[j++] = (*str)[i++];
			}
		}
		free((*str));
		(*str) = ft_strdup(tmp);
		free (tmp);
	}
}


// wanna make a copy of your double array , use phil function ... its your friend
char **phil(char **str)
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

int in_env(char *ptr, char **env, int flag) //this function cheeck if a pointer ptr is in the envirement and also save the env , you can  change it by sending 1 as a flag , it returns 1 in case the ptr its  exists in the env else it return 0
{
	static char **the_env;
	int k;
	int h;

	if (flag == 1)
	{
		if (!the_env)
		{
			the_env = phil(env);
		}
		else if (env)
		{
			free_double_array(the_env);
			the_env = phil(env);
		}
		return (2);
	}
	k = 0;
	while (the_env[k])
	{
		h = ft_strlen (ptr);
		if (!ft_strncmp(the_env[k], ptr, h) && the_env[k][h] == '=')
			return (1);
		k++;
	}
	return (0);
	
}

int checking_direction(char *str, char *behind_str) //this function take a look the expand to make it more exact ...
{
	char *tmp;
	int end;
	int i;
	char **split;

	if (behind_str)
	{
		if (!surounded_by(str, '\'') && !surounded_by(str, '\"') && !char_counter(str, ' ') && (!ft_strncmp(behind_str, "<<", 2)))
			return (0);
		else if (!surounded_by(str, '\'') && !surounded_by(str, '\"') && !char_counter(str, ' ') && (!ft_strncmp(behind_str, ">>", 2) || !ft_strncmp(behind_str, "<", 1) || !ft_strncmp(behind_str, ">", 1)))
		{
			end = ft_simularity_len(str, '$');

			while (str[end + 1] && (ft_isalpha(str[end + 1]) || ft_isdigit((str[end + 1])) || (str[end + 1] == '_')))
				end++;

			tmp = take_copy(str, ft_simularity_len(str, '$') + 1, end);
			if (in_env(tmp, NULL, 0))
			{
				free (tmp);
				return (1);
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
					end = checking_direction(split[i], split[i - 1]);

					break;	
				}
			printer(split);
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
					end = checking_direction(split[i], split[i - 1]);

					break;	
				}
			printer(split);
			free_double_array(split);
			return (end);
		}
	}
	return (1);
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
			else 
				j++;
		}
		str[i] = ft_calloc (sizeof (char) ,(ft_strlen ((*str_pro_max)[i]) + k + 1) * (char_counter((*str_pro_max)[i], '$') + 1));
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
			if (i > 0)
				to_expand = checking_direction((*str_pro_max)[i], (*str_pro_max)[i - 1]);
			else
				to_expand = checking_direction((*str_pro_max)[i], NULL);

			if (!surounded_by((*str_pro_max)[i], '\'') && to_expand)
			{
				free ((*str_pro_max)[i]);
				(*str_pro_max)[i] = ft_strdup(str[i]);
			}
			else
				i_should_replace_them(&(*str_pro_max)[i]);
		}
		i++;
	}
	free_double_array(str);
}

// te perfect parsing does not exis ... 
char *parsing(char **input, char **env)
{
	char **new_str;
	char **str_pro_max; // the best one to use till moument

//	delete_non_sense(input);
	new_str = split_without_weast (input);
	if (ft_strlen ((*input)) && !ft_strcount (new_str))
	{
		error_print ("syntax error", NULL);
		free_double_array(new_str);
		return (NULL);
	}
	expand(&new_str, env);
	str_pro_max = ultra_split(new_str, input);
	the_joiner(&str_pro_max);
	no_etxra_qoutes(&str_pro_max);
	//printer(new_str);
	printer(str_pro_max);
	free_double_array(new_str);
	free_double_array(str_pro_max);
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	char *input;
	char *copy;
	char **split;

	(void)ac;
	(void)av;
	in_env(NULL, env, 1);
	printf("\033[1mThe default interactive shell is now zsh.\nTo update your account to use zsh, please run chsh -s /bin/zsh.\n\033[0m");
	while (1)
	{
		input = readline("\033[1mbash-3.2$> \033[0m");
		if (input == NULL)
		{
			printf ("exit\n");
			free (input);
			break;
		}
		if (!ft_strncmp(input, "exit", 6))
		{
			free (input);
			break;
		}
		copy = ft_strdup(input);
		if (char_counter(copy, '\"') || char_counter(copy, '\''))
			parsing(&copy, env);
		else
		{
			make_some_space(&copy);
			split = ft_split (copy, ' ');
			expand (&split, env);
			printer (split);
			free_double_array(split);
		}
		free (copy);
		add_history(input);
		free(input);
	}
	return 0;
}

