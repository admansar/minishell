#include "../minishell.h"

int found_in_middle(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ':' && str[i + 1] == ':')
			count++;
		i++;
	}
	return (count);
}

char	*ft_fix_path(char *str, int in_mid)
{
	char *fixed;
	int i;
	int j;

	i = 0;
	j = 0;
	fixed = (char *) ft_calloc(sizeof(char) , ft_strlen(str) + in_mid + 1);
	while (str[i])
	{
		if (str[i] == ':' && str[i + 1] == ':')
		{
			fixed[j++] = ':';
			fixed[j++] = '.';
			fixed[j]= ':';
			i+=2;
		}
		else
			fixed[j] = str[i];
		j++;
		i++;
	}
	free(str);
	return (fixed);
}

int	have_just_digits(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-')
		i++;
	while (c[i])
	{
		if (ft_isdigit(c[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_list_size(t_input *list)
{
	int	i;

	i = 0;
	if (!list)
		return (i);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}
