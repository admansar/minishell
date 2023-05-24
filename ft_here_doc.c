
#include "minishell.h"

unsigned int ft_random(void)
{
    static unsigned int rand = 0;
	char *p;
	int i;

	p = malloc (sizeof (char) * 2);
	i = (unsigned char)&p[0];
    rand = ((rand + i) * 1103515245 + 12345) & 0xFFFFFFFF;
	free (p);
    return (rand);
}

char	*ft_generate_rand_str(int len)
{
    const char	src[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char		*random_str;
    int			src_len;
    int			i;
	int			random_i;

	random_str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	src_len = sizeof(src) - 1;
	while (i < len)
	{
        random_i = ft_random() % src_len;
        random_str[i++] = src[random_i];
	}
    random_str[i] = 0;
    return random_str;
}

int *ft_get_operators_pos(t_input *list, char *str, int *count)
{
	int *pos;
	int i;
	int j;

	*count = 0;
	j = 0;
	i = -1;
	while (list->redirect->type[++i])
		if (!ft_strcmp(list->redirect->type[i], str))
			(*count)++;
	if (*count == 0)
		return (NULL);
	pos = ft_calloc(sizeof(int), *count);
	i = -1;
	while (list->redirect->type[++i])
		if (!ft_strcmp(list->redirect->type[i], str))
			pos[j++] = i;
	return (pos);
}

void	ft_join_str_to_double_array(char ***arg, char **to_join)
{
	int len;
	int i;
	char	**joined;

	len = ft_strcount((*arg));
	joined = (char **)ft_calloc(sizeof(char *), len + 2);
	i = -1; 
	while ((*arg)[++i])
		joined[i] = ft_strdup((*arg)[i]);
	joined[i] = ft_strdup(*to_join);
	free_double_array((*arg));
	(*arg) = joined;
}

// launch here-doc as many times as it appear in the input
void	ft_here_doc(t_input *list, int *pos, t_redir *data, char **env)
{
	char	*input;
	char	*tmp;
	char	*to_expand;
	char	*expanded;
	char	*dollar_str;
	char	*ruin_name;
	int		i;
	int		j;
	int		rand;
	int		in_fd;

	data->expand = 1;
	i = 0;
	rand = ft_random() % 63;
	ruin_name = ft_generate_rand_str(data->herdoc_count + rand);
	tmp = ft_strjoin("/tmp/", ruin_name);
	free(ruin_name);
	list->redirect->herdoc_file_name = ft_strdup(tmp);
	if (data->herdoc_count)
	{
		in_fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		close(in_fd);
	}
	//unlink (tmp);
	while (i < data->herdoc_count)
	{
		if (surounded_by(list->redirect->file_name[pos[i]] , '\"')
			|| surounded_by(list->redirect->file_name[pos[i]], '\''))
		{
			no_surounded_anymore(&(list->redirect->file_name[pos[i]]));
			data->expand = 0;
		}
		while (1)
		{
			input = readline("> ");
			if (!input)
				break;
			if (!ft_strcmp(input, list->redirect->file_name[pos[i]]))
			{
				free(input);
				input = NULL;
				close(in_fd);
				break;
			}
			else if (i == data->herdoc_count - 1)
			{
				in_fd = open(tmp, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (input[0] == '$' && data->expand)
				{
					j = 0;
					while (input[j])
					{
						if (input[j] == '$')
							j++;
						else
							break;
					}
					dollar_str = take_copy(input, 0 , j - 2);
					write(in_fd, dollar_str, ft_strlen(dollar_str));
					to_expand = take_copy(input, j, ft_strlen(input));
					int pos_env = ft_in_env(to_expand, env);
					if (pos_env >= 0)
					{
						ft_get_var_value(env[pos_env], to_expand, &expanded);
						write(in_fd, expanded, ft_strlen(expanded));
						write(in_fd, "\n", 1);
						free(expanded);
					}
					free(dollar_str);
					free(to_expand);
				}
				else
				{
					write(in_fd, input, ft_strlen(input));
					write(in_fd, "\n", 1);
				}
			}
			free(input);
		}
		i++;
	}
	free(tmp);
}

void	ft_execute_here_docs(t_input *list, t_redir *data, char ***env, char ***export)
{
	t_input	*tmp;

	tmp = list;
	data->env = env;
	data->export = export;
	data->herdoc_count = 0;
	data->output_count = 0;
	while (tmp)
	{
		if (tmp->redirect->position)
		{
			data->pos_herdoc = ft_get_operators_pos(tmp, HERDOC, &(data->herdoc_count));
			data->pos_output = ft_get_operators_pos(tmp, OUTPUT, &(data->output_count));
			ft_here_doc(tmp, data->pos_herdoc, data, *env);
			free(data->pos_output);
			free(data->pos_herdoc);
		}
		tmp = tmp->next;
	}
}
