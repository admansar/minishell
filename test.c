#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include "libft/ft_printf.h"

//how many worlds before the letter indicated as the second char 
int ft_simularity_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

void delete_both(char **input, int start, int end, char c)
{
	int i;
	int j;
	char *re;

	re = malloc (sizeof (char) * ft_strlen((*input)) - 1);
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
	while (i < end - start + 1)
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
	while (co[++i] && co)
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

// no comment 
int surounded_by(char *str, char c)
{
	int h;

	h = ft_strlen (str);
	if (h > 0)
		if (str[0] == c && str[h - 1] == c)
			return (1);
	return (0);
}

//copy without beeing surounded by double quote
char *clean_copy(char *c)
{
	int i;
	int j;
	char *re;

	if (surounded_by(c, '\"'))
	{
		re = malloc (sizeof (char) * ft_strlen(c));
		i = 0;
		j = 0;
		while (c[i])
		{
			if (c[i] != '\"')
			{
				re[j] = c[i];
				j++;
			}
			i++;
		}
		re[j] = '\0';
		return (re);
	}
	return (c);
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

//no need to the comment !!
//anyway this function delete the double qoutes that start and end with nothing inside
void delete_non_sense(char **input)
{
	int i;
	int j;
	int taken;
	int start;
	int end;

	i = 0;
	j = 0;
	taken = 1;
	start = 0;
	end = 0;
	while ((*input)[i])
	{
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
			delete_both(input, start, end, '\"');
			i = -1;
			start = 0;
			end = 0;
			taken = 1;
		}
		i++;
	}
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
		if ((*input)[i] == '\"' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] != '\"' && taken == 1) 
		{
			new_str[j] = malloc (sizeof (char) * (ft_strlen((*input)) + 1));
			k = 0;
			while ((*input)[i] && (*input)[i] != '\"')
			{ 

				new_str[j][k] = (*input)[i];
				k++;
				i++;
			}
			new_str[j][k] = '\0';
			j++;
			i--;
		}
		else if ((*input)[i] == '\"' && taken == 0)
		{
			end = i;
			taken = 1;
		}
		if (start < end)
		{
			new_str[j++] = take_copy((*input), start, end);
			start = end;
		}
		i++;
	}
	new_str[j] = NULL;
	return (new_str);
}

//its not the same function !! 
//anyway this function split without wasting any letter but it make sure that the split is more reasonable to continue ... it pay attention to the most cases in the real bash 
char **split_and_pay_attention(char **input)
{
	int i;
	int j;
	int k;
	int taken;
	int start;
	int end;
	char **str;

	str = ft_calloc (sizeof (char *), ft_strlen((*input)));
	start = 0;
	end = 0;
	taken = 1;
	j = 0;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\"' && taken == 1)
		{
			start = i;
			taken = 0;
		}
		else if ((*input)[i] != '\"' && taken == 1) 
		{
			str [j] = malloc (sizeof (char) * (ft_strlen((*input))) + 1);
			k = 0;
			while ((*input)[i])
			{ 
				if ((i > 0) && (*input)[i] == '\"' && (*input)[i - 1] == ' ')
                break;
				str[j][k] = (*input)[i];
				k++;
				i++;
			}
			str[j][k] = '\0';
			j++;
			i--;
		}
		else if ((*input)[i] == '\"' && taken == 0)
		{
			if ((*input)[i + 1] == ' ' || (*input)[i + 1] == '\0' || (*input)[i + 1] == '\'')
			{
				end = i;
			}
			else
			{
				while ((*input)[i] != ' ' && (*input)[i] && (*input)[i + 1] != '\"')
					i++;
				end = i;
			}
			taken = 1;
		}
		if (start < end)
		{
			str[j++] = take_copy((*input), start, end);
			start = end;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}
//segv is here 
void rebuild(char **ptr)
{
	char *tmp;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if ((*ptr)[i] == '\'')
		return ;
	tmp = ft_calloc (sizeof(char), (2 + ft_strlen(*ptr)));
	tmp[j++] = '\"';
	while ((*ptr)[i])
	{
		if (k == 2 && (*ptr)[i] == ' ')
		{
			tmp[j++] = '\"';
			tmp[j++] = ' ';
			i++;
		}
		if ((*ptr)[i] != '\"')
		{
			tmp[j] = (*ptr)[i];
			j++;
		}
		else 
			k++;
			i++;
	}
	if (char_counter(tmp, '\"') != 2)
		tmp[j++] = '\"';
	tmp[j] = '\0';
	free (*ptr);
	*ptr = malloc (sizeof (char) * (ft_strlen(tmp) + 1));
	strlcpy(*ptr, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

void free_double_array(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		free(c[i++]);
	free(c);
}

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
		if (!char_counter(new_str[i], '\"') && char_counter(new_str[i], ' '))
		{
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
			str_pro_max[k++] = ft_strdup(new_str[i]);
		}
		i++;
	}
	return (str_pro_max);
}

char *parsing(char **input)
{
	int i;
	int j;
	int k;
	int taken;
	int start;
	char *must_fus;
	int end;
	char **str;
	char **new_str;
	char *tmp1;
	char *tmp2;
	char **str_pro_max; // the best one one use
	char **split;

	if (!char_counter((*input), '\"') && ! char_counter((*input), '\''))
		return (NULL);
	if (char_counter((*input), '\"') % 2 || char_counter((*input), '\'') % 2)
	{
		error_print ("bash: syntax error", NULL);
		return (NULL);
	}
	delete_non_sense(input);
	str = split_and_pay_attention (input);
	new_str = split_without_weast (input);
	if ((!surounded_by(str[0], '\"')) && char_counter(str[0], ' '))
	{
		k = ft_simularity_len (str[0], ' ') + 1;
		tmp1 = malloc (sizeof(char) * (k + 1));
		ft_strlcpy(tmp1, str[0], k + 1);
		tmp2 = ft_strdup (str[0] + k);
		free (str[0]);
		str[0] = ft_strdup(tmp1);
		free (tmp1);
		if (str[1])
		{
			must_fus = ft_str_join (tmp2, str[1]);
			ft_strlcpy(str[1], must_fus, ft_strlen (must_fus) + 1);
			free (must_fus);
		}
		else
		{
			str[1] = ft_strdup(tmp2);
			free (tmp2);
		}
	}
	i = 0;
	j = 0;
	while (new_str[i])
	{
		if ((char_counter(new_str[i], '\'') % 2))
		{
			error_print ("command not found: ", clean_copy(new_str[i]));
			free_double_array(new_str);
			return (NULL);
		}
		i++;
	}
	if (char_counter(new_str[0], ' ') && surounded_by(new_str[0], '\"'))
	{
		error_print ("command not found: ", clean_copy(new_str[0]));
		free_double_array(new_str);
		return (NULL);
	}
	i = -1;
	j = -1;
//	while (new_str[++i + 1])
//		if (new_str[i][ft_strlen(new_str[i]) - 1] != ' ')
//		{
//			new_str[i] = ft_str_join(new_str[i], new_str[i + 1]);
//			j = i + 1;
//			while (new_str[j + 1])
//			{
//				k = ft_strlen(new_str[j + 1]) + 1;
//				printf ("%d <<>> %d\n", j , k);
//				free (new_str[j]);
//				new_str[j] = malloc (sizeof(char) * k);
//				ft_strlcpy(new_str[j] , new_str[j + 1], k);
//				j++;
//			}
//			new_str[j] = NULL;
//		}
	str_pro_max = ultra_split(new_str, input);
//	i = 0;
//	while (str[i])
//	{
//		if (char_counter(str[i], '\"') == 2 && !surounded_by(str[i], '\"'))
//			rebuild(&str[i]);
//		i++;
//	}
	i = 0;
	while (new_str[i])
		printf ("%s$\n", new_str[i++]);
	printf ("-------%d\n", ft_strcount(new_str));
	i = 0;
	while (str[i])
		printf ("%s$\n", str[i++]);
	printf ("-------%d\n", ft_strcount(str));
	i = 0;
	while (str_pro_max[i])
		printf ("%s$\n", str_pro_max[i++]);
	printf ("-------%d\n", ft_strcount(str_pro_max));
	free_double_array(new_str);
	free_double_array(str);
	free_double_array(str_pro_max);
	return (NULL);
}

int main()
{
    char *input;
    printf("\033[1mThe default interactive shell is now zsh.\nTo update your account to use zsh, please run chsh -s /bin/zsh.\n\033[0m");
	input = (char *)1;
	while (1)
	{
  	  input = readline("\033[1mbash-3.2$> \033[0m");
	  if (!input)
	  {
		  printf ("\n");
		  break;
	  }
  	  parsing(&input);
  	  add_history(input);
	 //   ft_printf("%s\n", input);
  	  free(input);
	}
    return 0;
}

