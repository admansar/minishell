/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:52:20 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/03 17:40:57 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define OUTPUT "1"
# define APPEND "2"
# define INPUT "3"
# define HERDOC "4"

# define AMBIGUOUS 1
# define AMBIGUOUS_ERR 2
# define NO_FILE 3

typedef struct s_global
{
	int				g_exit_status;
	int				pid[PIPE_BUF];
	int				index;
}					t_global;

t_global			g_vars;

typedef struct s_files
{
	int				i;
	int				j;
	int				ret;
	int				*arr;
}					t_files;

typedef struct s_rand_str
{
	char			src[63];
	char			*random_str;
	int				src_len;
	int				i;
	int				random_i;
	char			*tmp;
	char			*ruin_name;
	int				rand_nbr;
}					t_rand_str;

typedef struct s_export
{
	char			**valid_export_vars;
	char			**valid_env_vars;
	char			**env_vars;
	char			*tmp_name;
	char			*tmp_value;
	char			*tmp1;
	char			*tmp2;
	int				*arr;
	int				var_nbr;
	int				j;
	int				i;
	int				count;
	int				ret;
	int				exist;
	int				len;
}					t_export;

typedef struct s_echo
{
	int				i;
	int				count;
	int				option;
	int				skip;
	int				j;
}					t_echo;

typedef struct s_cd
{
	char			*old_pwd;
	char			*pwd;
	char			*joined;
	char			*home_path;
	char			old_name[7];
	char			pwd_name[5];
	char			path[PATH_MAX];
	int				index_pwd;
	int				index_old_pwd;
	int				home_index;
}					t_cd;

typedef struct s_redir
{
	char			***env;
	char			***export;
	int				*pos_herdoc;
	int				*pos_output;
	char			*input;
	int				herdoc_count;
	int				input_count;
	int				output_count;
	int				append_count;
	int				her_doc;
	int				output;
	int				out_fd;
	int				in_fd;
	int				error;
	int				expand;
	int				count;
	int				pid;
}					t_redir;

typedef struct s_redirection
{
	char			**type;
	int				position;
	char			**file_name;
	char			*herdoc_file_name;
}					t_redirection;

typedef struct s_input
{
	char			*cmd;
	char			**arg;
	t_redirection	*redirect;
	int				pipe;
	struct s_input	*next;
}					t_input;

/*****************************************************************/
/*                           EXECUTION                           */
/*****************************************************************/

void				ft_execution(t_input *list, char ***env, char ***export);
char				*take_copy(char *s1, int start, int end);
int					in_env(char *ptr, char **env, int flag);
int					ft_simularity_len(char *str, char c);
int					ft_simularity_len_dual(char *str, char c);
void				free_double_array(char **c);
void				ft_pipe(t_input *list, t_redir *data, char ***env,
						char ***export);
void				ft_exec(t_input *list, char ***envi, char ***export);
void				printer(char **ptr);
int					char_counter(const char *co, char c);

/***************************************************************/
/*                         EXPORT/UNSET                        */
/***************************************************************/

void				ft_export(char ***env, t_input *list, char ***export);
void				ft_unset(char ***env, t_input *list, char ***export);
void				ft_get_var_name(char *var, char **var_name);
void				ft_get_var_value(char *var, char *var_name,
						char **var_value);
int					ft_get_var(char *var, char **name, char **value);
void				ft_check_env_var(t_export *data);
void				ft_clean_up_name(char **str);
int					mega_counter(char **str, char c);
int					ft_unset_name_checker(char *str);
int					ft_export_name_checker(char *str);
char				**ft_join_double_ptr_to_ptr(char *str, char **arr1);
void				ft_init_export_data(t_export *data);

/*******************************************************************/
/*                            BUILT-INS                            */
/*******************************************************************/

int					ft_in_env(char *ptr, char **env);
char				*ft_create_var(char *name, char *value);
char				**fill(char **str);
/********************UTILS********************/
void				ft_change_directory(t_input *list, char ***env,
						char ***export);
void				ft_pwd(void);
void				ft_echo(t_input *list);

int					ft_strcmp(const char *s1, const char *s2);
void				ft_redirections(t_input *list, t_redir *data, char ***env,
						char ***export);
int					*ft_get_operators_pos(t_input *list, char *str, int *count);
void				ft_update_value_env(char *arr, char ***ptr, int pos);
void				ft_get_var_value(char *var, char *var_name,
						char **var_value);
char				**ft_join_ptr_to_double_ptr(char **arr1, char *str);
int					ft_list_size(t_input *list);
void				ft_execute_here_docs(t_input *list, t_redir *data,
						char ***env, char ***export);
int					surounded_by(char *str, char c);
void				no_surounded_anymore(char **str);
int					ft_in_env(char *str, char **env);
int					ft_char_checker(char *str, char c);
void				ft_get_var_name(char *var, char **var_name);
void				ft_get_var_value(char *var, char *var_name,
						char **var_value);
int					ft_unset_name_checker(char *str);
int					ft_export_name_checker(char *str);
void				ft_clean_up_name(char **str);
char				**ft_join_double_ptr_to_ptr(char *str, char **arr1);
char				**ft_join_ptr_to_double_ptr(char **arr1, char *str);
char				**ft_double_array_joiner(char **arr1, char **arr2);
void				ft_join_str_to_double_array(char ***arg, char **to_join);
void				exchange(char **ptr, char c, char b);
void				disable(char **str, char c);
void				ft_update_last_command(char ***env, t_input *list);
void				ft_update_exit_status(char ***env);
void				array_expander(char **ptr, char **env);
void				no_extra_(char **ptr, char c);
int					consecutive(char *str, char c);
void				wildcard(char ***split);
char				*clean_from(char *c, char l);
void				ft_export_printer(t_input *list, char **export,
						t_export *data);
unsigned int		ft_random(void);
char				*ft_generate_rand_str(int len);
void				ft_get_rand_str(t_rand_str *d, t_redir *data,
						t_input *list);
void				ft_check_expand(t_input *list, t_redir *data, int *pos,
						int i);
void				ft_leave_current_heredoc(t_redir *data, int i);
int					inside_of(char *str, char c);
void				init_vars(t_redir *data);
int					ambiguous_check_1(t_input *list, t_redir *data, int i);
int					ambiguous_check_2(t_input *list, t_redir *data, char *tmp,
						int i);
int					ft_early_ambiguous_check(t_input *list, t_redir *data);
void				ft_error(t_redir *data, int flag);
int					ft_ambiguous(t_input *list, t_redir *data, int i);
void				ft_get_all_fds(t_files *f_data, t_input *list,
						t_redir *data);
int					ft_check_permissions(t_input *list, t_redir *data,
						t_files *f_data, int flag);
int					file_found(t_input *list, t_files *f_data);
void				ft_create_file(t_input *list, t_redir *data,
						t_files *f_data, int flag);
void				get_out_fd(t_files *f_data, t_redir *data);

#endif
