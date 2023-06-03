#include "../minishell.h"

// check if the char c is found inside of the string str
int inside_of(char *str, char c)
{
	int len;
	int i;

	i = 1;
	len = ft_strlen (str) - 1;
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

// check if there is consecutive character in the string
int	consecutive(char *str, char c)
{
	int i;
	int len;

	len = ft_strlen(str) - 1;
	i = 0;
	while (str[i+1])
	{
		if (str[i] == c && str[i+1] == c && i + 1 != len)
			return (1);
			i++;
	}
	return (0);	
}

// create a new str without the specified character in it
char *clean_from (char *c, char l)
{
	int i;
	int j;
	char *re;

	i = 0;
	j = 0;
	re = malloc (sizeof (char) * (ft_strlen (c) + 1));
	while (c && c[i])
	{
		if (c[i] != l)
			re[j++] = c[i++];
			else 
			i++;
	}
	re[j] = '\0';
	return (re);
}

void	init_vars(t_redir *data)
{
	data->error = 0;
	data->in_fd = 0;
	data->out_fd = 0 ;
}