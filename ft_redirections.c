
#include "minishell.h"

// return an array that has the position of each str in the "list->redirect->type"
int *ft_get_operators_pos(t_input *list, char *str, int *count)
{
	int *pos;
	int i;
	int j;

	*count = 0;
	j = 0;
	i = -1;
	while (list->redirect->type[++i])
	{
		if (!ft_strcmp(list->redirect->type[i], str))
			(*count)++;
	}
	if (*count == 0)
		return (NULL);
	pos = ft_calloc(sizeof(int), *count);
	i = -1;
	while (list->redirect->type[++i])
		if (!ft_strcmp(list->redirect->type[i], str))
			pos[j++] = i;
	return (pos);
}

// launch here-doc as many times as it appear in the input
void ft_here_doc(t_input *list, int herdoc_count, int *pos, char ***env,char ***export)
{
	char *input;
	int i;

	i = 0;
	while (i < herdoc_count)
	{
		while (1)
		{
			input = readline("> ");
			if (!ft_strcmp(input, list->redirect->file_name[pos[i]]))
			{
				free(input);
				input = NULL;
				break;
			}
			if (input)
				free(input);
		}
		if(list->cmd)
			ft_exec(list, env, export);
		i++;
	}
}

void ft_input_redirection(t_input *list, int input_count, int *pos, char ***env, char ***export)
{
	int i;
	int input_fd;
	int	stdin_fd;

	i = 0;
	if (input_count > 0)
	{
		while (i < input_count)
		{
			if (access(list->redirect->file_name[pos[i]], F_OK | R_OK) == -1)
			{
				printf("bash: %s: No such file or directory\n"
					, list->redirect->file_name[pos[i]]);
				i = input_count;
				break;
			}
			else
			{
				input_fd = open(list->redirect->file_name[pos[i]], O_RDONLY);
			}
			i++;
		}
		stdin_fd = dup(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		if (list->cmd)
			ft_exec(list, env, export);
		dup2(stdin_fd , STDIN_FILENO);
		close(stdin_fd);
	}
}

void ft_output_redirection(t_input *list, int output_count, int *pos, char ***env, char ***export)
{
	int i;
	int output_fd;
	int stdout_fd;

	if (output_count > 0)
	{
		i = 0;
		while (i < output_count)
		{
			output_fd = open(list->redirect->file_name[pos[i]]
				, O_RDWR | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		stdout_fd = dup(STDOUT_FILENO);
		dup2(output_fd, STDOUT_FILENO);

		close(output_fd);
		if (list->cmd)
			ft_exec(list, env, export);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}

void ft_append_redirection(t_input *list, int append_count, int *pos, char ***env, char ***export)
{
	int i;
	int output_fd;
	int stdout_fd;

	if (append_count > 0)
	{
		i = 0;
		while (i < append_count)
		{
			output_fd = open(list->redirect->file_name[pos[i]]
				, O_RDWR | O_CREAT | O_APPEND, 0644);
			i++;
		}
		stdout_fd = dup(STDOUT_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		if (list->cmd)
			ft_exec(list, env, export);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}

void ft_redirections(t_input *list, char ***env, char ***export)
{
	int herdoc_count;
	int input_count;
	int output_count;
	int append_count;
	int *pos;

	pos = ft_get_operators_pos(list, HERDOC, &herdoc_count);
	ft_here_doc(list, herdoc_count, pos, env, export);
	free(pos);
	pos = ft_get_operators_pos(list, INPUT, &input_count);
	ft_input_redirection(list, input_count, pos, env, export);
	free(pos);
	pos = ft_get_operators_pos(list, OUTPUT, &output_count);
	ft_output_redirection(list, output_count, pos, env, export);
	free(pos);
	pos = ft_get_operators_pos(list, APPEND, &append_count);
	ft_append_redirection(list, append_count, pos, env, export);
	free(pos);
}
