/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:52:20 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/21 22:48:15 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/errno.h>

#define OUTPUT "1"
#define INPUT "3"
#define HERDOC "4"
#define APPEND "2"
#define MAX_PATH 4096

int g_exit_status;

typedef struct s_redir
{
	char		***env;
	char		***export;
	int			herdoc_count;
	int 		input_count;
	int			output_count;
	int			append_count;
	int			*pos_herdoc;
	int			*pos_output;
	int			*pos_input;
	int			*pos_append;
	int			output;
	int			input;
	int			out_fd;
	int			in_fd;
	int			her_doc;
	int			input_error;
}				t_redir;

typedef struct s_redirection
{
	char			**type;
	int				position; 
	char			**file_name;
	char			*herdoc_file_name;
}					t_redirection;

typedef struct s_input
{
	char				*cmd;
	char				**arg;
	t_redirection		*redirect;
	int					pipe;
	struct s_input		*next;
}						t_input;


void ft_execution(t_input *list, char ***env, char ***export);
char *take_copy(char *s1, int start, int end);
int in_env(char *ptr, char **env, int flag);
int ft_simularity_len(char *str, char c);
void free_double_array(char **c);
void	ft_pipe(t_input *list, t_redir *data,char ***env, char ***export);
void ft_exec(t_input *list, char ***envi, char ***export);
void printer(char **ptr);
int char_counter(const char *co, char c);


/********************EXPORT/UNSET********************/

void	ft_export(char ***env, t_input *list, char ***export);
void	ft_unset(char ***env, t_input *list, char ***export);
void	ft_export_printer(char **export);
void	ft_get_var_name(char *var, char **var_name);
void	ft_get_var_value(char *var, char *var_name, char **var_value);
int		ft_get_var(char *var, char **name, char **value);
char	**ft_check_env_var(char **valid_export_vars);
void	ft_clean_up_name(char **str);
int		mega_counter(char **str, char c);
int		ft_unset_name_checker(char *str);
int		ft_export_name_checker(char *str);
char	**ft_join_double_ptr_to_ptr(char *str, char **arr1);

/********************BUILT-IN UITLS********************/
int		ft_in_env(char *ptr, char **env);
char	*ft_create_var(char *name, char *value);
char	**fill(char **str);
void    ft_change_dir(t_input *list, char ***env, char ***export);
void    ft_pwd();
void    ft_echo(t_input *list);


/********************UTILS********************/
int		ft_strcmp(const char *s1, const char *s2);
void	ft_redirections(t_input *list, t_redir *data, char ***env, char ***export);
int		*ft_get_operators_pos(t_input *list, char *str, int *count);
void	ft_update_value_env(char *arr , char ***ptr, int pos);
void	ft_get_var_value(char *var, char *var_name, char **var_value);
char	**ft_join_ptr_to_double_ptr(char **arr1, char *str);
int		ft_list_size(t_input *list);
void	ft_execute_here_docs(t_input *list, t_redir *data, char ***env, char ***export);

#endif
