/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:17:33 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/14 11:42:16 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

// typedef struct s_mini
// {
// 	char 			*cmd;
// 	char 			**args;
// 	char 			*operator;
// 	struct s_mini	*next;
// }				t_mini;

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
void ft_execution(t_input *list, char ***env, char ***export)
{
	// (void)env;
	t_input *tmp;

	tmp = list;

	// while (tmp)
	// {
	// 	if (tmp->cmd)
	// 	printf("%s\n", tmp->cmd);
	// 	printer(tmp->arg);
	// 	if (tmp->redirect->type)
	// 	{
	// 		printf("%d\n", tmp->redirect->type);
	// 		printer(tmp->redirect->file_name);
	// 	}
	// 	if (tmp->pipe)
	// 		printf("|\n");
	// 	tmp = tmp->next;
	// }
	
	// printf("\n###############################\n");
	
	// printf("%s\n", list->cmd);

	// char name[] = "variable";
	// char value[] = "variable value so dont worry";
	
	// char value1[] = "hello world";
	// char value2[] = "hello world";
	// char name2[] = "var";
	
	tmp = list;
	if (!ft_strncmp(tmp->cmd, "export", 7))
		ft_export(env, list, export);
	else if (!ft_strncmp(tmp->cmd, "unset", 7))
		ft_unset(env, list, export);
	else if (!ft_strncmp(tmp->cmd, "env", 4))
		printer(*env);
	else 
		ft_pipe(list, *env);
	// else 
	// 	ft_execute(env , export, list);
}



void ft_exec(t_input *list, char **envi)
{
	(void)list;
	int id1;
	int inside;
	char *tmp;
	char **env;
	char **acces;
	char **arg;
	char **env_support;
	int found;
	int	i;

	inside = ft_in_env("PATH", envi);
	if (access(list->cmd, F_OK | X_OK) + 1 && !ft_strncmp(list->cmd, "./", 3))
	{
		id1 = fork();
		if (id1 == 0)
		{
			arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
			execve(list->cmd, arg, envi);
			free(arg);
		}
		wait(NULL);
	}
	else if (char_counter(list->cmd, '/') && access(list->cmd, F_OK | X_OK) + 1)
	{
		id1 = fork();
		if (id1 == 0)
		{
			env = ft_calloc (2, sizeof (char *));
			env[0] = take_copy (list->cmd, ft_strrchr(list->cmd, '/') - list->cmd, ft_strlen (list->cmd));
			arg = ft_join_double_ptr_to_ptr(list->cmd, list->arg);
			execve(list->cmd, arg, env);
			free_double_array (env);
			free (arg);
		}
		wait (NULL);
	}
	else if (inside + 1 && !char_counter(list->cmd, '/'))
	{
		tmp = take_copy(envi[inside], ft_simularity_len(envi[inside],'=') + 1, ft_strlen (envi[inside]));
		env = ft_split (tmp, ':');
		free (tmp);
		acces = ft_calloc (sizeof (char *), ft_strcount (env) + 1);
		i = 0;
		while (env[i])
		{
			tmp = ft_strjoin ("/", list->cmd);
			acces[i] = ft_strjoin(env[i], tmp);
			free (tmp);
			i++;
		}
		i = 0;
		found = 0;
		while (acces[i])
		{
			if (access(acces[i], F_OK | X_OK) + 1)
			{
				found = 1;
				break;
			}
			i++;
		}
		if (found)
		{
			id1 = fork();
			if (id1 == 0)
			{
				env_support = ft_calloc (sizeof (char *), 2);
				env_support[0] = ft_strdup (acces[i]);
				arg = ft_join_double_ptr_to_ptr(acces[i], list->arg);
				execve(acces[i], arg, env_support);
				free_double_array(env_support);
				free(arg);
			}
			wait (NULL);
		}
		else
		{
			printf ("bash: %s: command not found\n", list->cmd);
		}
		free_double_array(env);
		free_double_array(acces);
	}
	else
	{
		printf ("bash: %s: command not found\n", list->cmd);
	}

}

void ft_pipe(t_input *list, char **envi)
{
	(void)list;
	int pipe_fd[2];
	int pid1;
	int pid2;

	if (!list->pipe)
	{
		ft_exec(list, envi);
		return ;
	}
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
		ft_exec(list, envi);
		exit(1);
//		char *args[] = {"/bin/ls", "-la", NULL};
//		char *env[] = {"/bin", NULL};
//		execve("/bin/ls", args, env);
	}
	list = list->next;
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
		ft_exec(list, envi);
		exit(1);
	//	char *args[] = {"/usr/bin/sort",NULL, NULL};
	//	char *env[] = {"/usr/bin", NULL};
	//	execve("/usr/bin/sort", args, env);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
}
