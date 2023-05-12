/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:17:33 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/12 12:43:10 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_check_access(char **paths, char *cmd)
{
	int i;

	i = 0;
	while (paths[i])
	{
		if (!access(ft_str_join(paths[i], cmd), X_OK))
			printf("commande found\n");
		else
			printf("commande not found :\n");
		i++;
	}
}

// add slash at the end of each path
char *ft_add_slash(char *path)
{
	char *new_path;
	int size;
	int i;
	int j;

	size = ft_strlen(path) + count_words(path, ':');
	new_path = (char *)ft_calloc(sizeof(char), size + 1);
	if (!new_path)
		return (NULL);
	new_path[size - 1] = '/';
	i = -1;
	j = 0;
	while (path[++i])
	{
		if (path[i] != ':')
			new_path[j] = path[i];
		else if (path[i] == ':')
		{
			new_path[j++] = '/';
			new_path[j] = path[i];
		}
		j++;
	}
	free(path);
	return (new_path);
}

// get PATH value from evn variable
char	*ft_getenv(char **env ,char *path)
{
	char *tmp;
	int i ;

	tmp = env[in_env(path, NULL, 0)];
	i = ft_simularity_len(tmp, '=');
	tmp = take_copy(tmp, i + 1, ft_strlen(tmp));
	return (tmp);
}

// split the path after adding backslash to it
char **ft_get_path(char **env)
{
	(void)env;
	char *path;
	char **split;

	path = ft_getenv(env, "PATH");
	path = ft_add_slash(path);
	split = ft_split(path, ':');
	free(path);
	return (split);
}

// execution
void ft_execution(t_input *list, char ***env)
{
	(void)env;
	t_input *tmp;

	tmp = list;

	// printer(*env);
	while (tmp)
	{
		if (tmp->cmd)
	//	printf("%s\n", tmp->cmd);
		printer(tmp->arg);
		if (tmp->redirect->type)
		{
	//		printf("%d\n", tmp->redirect->type);
			printer(tmp->redirect->file_name);
		}
//		if (tmp->pipe)
//			printf("|\n");
		tmp = tmp->next;
	}
	
	// printf("\n###############################\n");
	
	// printf("%s\n", list->cmd);

	// char name[] = "variable";
	// char value[] = "variable value so dont worry";
	
	// char value1[] = "hello world";
	// char value2[] = "hello world";
	// char name2[] = "var";
	
	tmp = list;
	if (!ft_strncmp(tmp->cmd, "export", ft_strlen(tmp->cmd)))
		ft_export(env, list);

	// ft_unset(env, name);
}

void ft_pipe(t_input *list)
{
	(void)list;
	int pipe_fd[2];
	int pid1;
	int pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		char *args[] = {"/bin/ls", "-la", NULL};
		char *env[] = {"/bin", NULL};
		execve("/bin/ls", args, env);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		char *args[] = {"/usr/bin/sort",NULL, NULL};
		char *env[] = {"/usr/bin", NULL};
		execve("/usr/bin/sort", args, env);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
}
