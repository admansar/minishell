#include "minishell.h"

void	print_triple_ptr(char ***str)
{	
	int i;

	i = 0;
	while (str[i])
	{
		printer(str[i++]);
		printf("\n-----------\n");
	}
}

char	*my_strjoin(char *readed, char *buff)
{
	char	*join;
	int		i;
	int		j;

	join = malloc((ft_strlen(readed) + ft_strlen(buff) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	if (readed)
	{
		while (readed[i])
		{
			join[i] = readed[i];
			i++;
		}
	}
	j = -1;
	while (buff[++j])
		join[i + j] = buff[j];
	join[i + j] = 0;
	free(readed);
	return (join);
}

char	**ft_read_dir()
{
    DIR *dir;
    struct dirent *entry;
	char	*all;
	char	**split;

	all = NULL;
    dir = opendir(".");
    if (dir == NULL)
	{
        printf("Could not open the directory.\n");
        return NULL;
    }
	entry = readdir(dir);
    while (entry)
	{
		all = my_strjoin(all, entry->d_name);
		all = my_strjoin(all, " ");
		entry = readdir(dir);
    }
    closedir(dir);
	split = ft_split(all , ' ');
	free(all);
    return (split);
}

void	ft_wildcard(char ***str)
{
	(void)str;
	char	***wild_expantions;
	char	**dir_content;
	int		file_nbr;
	char	**sets;
	int		symb_pos;
	// char	*prefix;
	// char	*suffix;
	char	*tmp;
	int j = 0;
	int k = 0;
	int x;
	int y;
	int count = 0;
	
	dir_content = ft_read_dir();
	file_nbr = ft_strcount(dir_content);
	// printer(dir_content);
	// printf("\n+--------------+\n");
	int i = 0;
	while ((*str)[i])
	{
		if (!strncmp((*str)[i], "*", 2))
			count += file_nbr;
		else
		{
			symb_pos = ft_char_checker((*str)[i], '*');
			if (symb_pos >= 0
				&& !(surounded_by((*str)[i], '\"') || surounded_by((*str)[i], '\'')))
			{
				sets = ft_split((*str)[i], '*');
				j = 0;
				while (sets[j])
				{
					count++;
					j++;
				}
			}
		}
		i++;
	}
	printf("the count is : %d\n", count);
	wild_expantions = (char ***)ft_calloc(sizeof(char **), count + 10);
	i = 0;
	j = 0;
	k = 0;
	while ((*str)[i])
	{
		if (!strncmp((*str)[i], "*", 2))
		{
			wild_expantions[k++] = (char **)ft_calloc (sizeof(char *), file_nbr + 10);
		}
		else
		{
			symb_pos = ft_char_checker((*str)[i], '*');
			if (symb_pos >= 0
				&& !(surounded_by((*str)[i], '\"') || surounded_by((*str)[i], '\'')))
			{
				sets = ft_split((*str)[i], '*');
				j = 0;
				while (sets[j])
				{
					wild_expantions[k++] = (char **)ft_calloc (sizeof(char *), file_nbr + 10);	
					j++;
				}
			}
		}
		i++;
	}
	printf("nbr of allocated double ptr : %d\n", k);
	i = 0;
	j = 0;
	k = 0;
	x = 0;
	y = 0;
	while ((*str)[i])
	{
		if (!strncmp((*str)[i], "*", 2))
		{
			while (dir_content[k])
			{
				wild_expantions[x][y++] = ft_strdup(dir_content[k]);
				k++;
			}
			x++;
		}
		else
		{
			symb_pos = ft_char_checker((*str)[i], '*');
			if (symb_pos >= 0
				&& !(surounded_by((*str)[i], '\"') || surounded_by((*str)[i], '\'')))
			{
				sets = ft_split((*str)[i], '*');
				j = 0;
				while (sets[j])
				{
					k = 0;
					y = 0;
					while (dir_content[k])
					{
						tmp = ft_strnstr(dir_content[k], sets[j], ft_strlen(dir_content[k]));
						if (tmp)
						{
							// printf("x : %d\n" , x);
							// printf("y : %d\n---------\n" , y);
							wild_expantions[x][y] = ft_strdup(tmp);
							y++;
						}
						k++;
					}
					x++;
					j++;
				}
			}
		}
		i++;
	}
	print_triple_ptr(wild_expantions);
	i = 0;
	j = 0;
	k = 0;
	
	
	return;
}


	// while ((*str)[i])
	// {
	// 	if (!strncmp((*str)[i], "*", 2))
	// 		count += file_nbr;
	// 	else
	// 	{
	// 		symb_pos = ft_char_checker((*str)[i], '*');
	// 		if (symb_pos >= 0
	// 			&& !(surounded_by((*str)[i], '\"') || surounded_by((*str)[i], '\'')))
	// 		{
	// 			sets = ft_split((*str)[i], '*');
	// 			j = 0;
	// 			while (sets[j])
	// 			{
	// 				k = 0;
	// 				while (dir_content[k])
	// 				{
	// 					tmp = ft_strnstr(dir_content[k], sets[j], ft_strlen(dir_content[k]));
	// 					if (tmp != NULL)
	// 						count++;
	// 					k++;
	// 				}
	// 				j++;
	// 			}
	// 		}
	// 	}
	// 	i++;
	// }
			// printer(sets);
			// printf("set 0 ---->%s\n", sets[0]);
			// tmp = ft_strnstr(dir_content[6], sets[0], ft_strlen(dir_content[6]));
			// printf("set ---->%s\n", tmp);
			// tmp = ft_strnstr(dir_content[6], sets[1], ft_strlen(dir_content[6]));
			// printf("set ---->%s\n", tmp);
			// tmp = ft_strnstr(dir_content[6], sets[2], ft_strlen(dir_content[6]));
			// printf("set ---->%s\n", tmp);
			// printf("you can do your magic : at pos : %d\n", i);
			// prefix = take_copy((*str)[i], 0 , symb_pos - 1);
			// printf("prefix : %s\n",prefix);
			// suffix = take_copy((*str)[i], symb_pos  + 1, ft_strlen((*str)[i])); 
			// printf("suffix : %s\n",suffix);