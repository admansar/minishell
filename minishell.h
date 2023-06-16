/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:52:20 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/13 19:18:52 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <dirent.h>
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
	int				here_doc;
	char			**env;
	int				killed_heardoc;
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
	int				err;
}					t_rand_str;

typedef struct s_execution
{
	int				inside;
	char			*tmp;
	char			*tmp1;
	char			**env;
	char			**acces;
	char			**arg;
	int				in_mid;
	int				found;
	int				i;
	int				status;
}					t_execution;

typedef struct s_pipe
{
	int				**pipe_fd;
	int				pipe_num;
	int				i;
	int				j;
	int				status;
	char			***env;
	char			***export;
}					t_pipe;

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
	char			old_pwd_name[7];
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
	char			herdoc_file_name[30];
}					t_redirection;

typedef struct s_parse
{
	int				i;
	int				j;
	int				k;
	int				taken;
	int				start;
	int				end;
	float			used;
	int				len;
	char			*str;
}					t_parse;

typedef struct s_expand
{
	int				i;
	int				k;
	int				h;
	int				j;
	int				m;
	int				start;
	int				end;
	char			*tmp;
	char			*tmp2;
	char			**str;
	char			*re;
	int				to_expand;
}					t_expand;

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
int					ft_simularity_len_d(char *str, char c);
void				free_double_array(char **c);
void				ft_pipe(t_input *list, t_redir *data, char ***env,
						char ***export);
void				ft_exec(t_input *list, char ***envi, char ***export);
void				printer(char **ptr);
int					char_counter(const char *co, char c);
void				ft_export(char ***env, t_input *list, char ***export);
void				ft_unset(char ***env, t_input *list, char ***export);
int					ft_is_file_dir(t_input *list, t_redir *data,
						t_files *f_data);
void				ft_get_var_name(char *var, char **var_name);
void				ft_get_var_value(char *var, char *var_name,
						char **var_value);
void				ft_get_var(char *var, char **name, char **value);
void				ft_get_rand_str(t_rand_str *d, t_redir *data,
						t_input *list);
void				ft_check_env_var(t_export *data);
void				ft_clean_up_name(char **str);
int					mega_counter(char **str, char c);
int					ft_unset_name_checker(char *str);
int					ft_export_name_checker(char *str);
char				**ft_join_double_ptr_to_ptr(char *str, char **arr1);
void				ft_init_export_data(t_export *data);
void				ft_exit(t_input *list);
int					ft_in_env(char *ptr, char **env);
char				*ft_create_var(char *name, char *value);
char				**fill(char **str);
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
void				the_checker(char ***split);
char				*clean_from(char *c, char l);
void				ft_export_printer(t_input *list, char **export,
						t_export *data);
unsigned int		ft_random(void);
char				*ft_generate_rand_str(int len);
void				ft_check_expand(t_input *list, t_redir *data, int *pos,
						int i);
int					ft_leave_current_heredoc(t_redir *data, int i);
int					inside_of(char *str, char c);
void				init_vars(t_redir *data);
int					ambiguous_check_1(t_input *list, t_redir *data, int i);
int					ambiguous_check_2(t_input *list, t_redir *data, char *tmp,
						int i);
int					ft_early_ambiguous_check(t_input *list, t_redir *data);
void				ft_error(t_redir *data, int flag);
int					ft_ambiguous(t_input *list, t_redir *data, int i);
void				get_outfile_nbr(t_files *f_data, t_input *list,
						t_redir *data);
int					ft_check_permissions(t_input *list, t_redir *data,
						t_files *f_data, int flag);
int					file_found(t_input *list, t_files *f_data);
void				ft_create_file(t_input *list, t_redir *data,
						t_files *f_data, int flag);
void				get_out_fd(t_files *f_data, t_redir *data);
int					found_in_middle(char *str);
char				*ft_fix_path(char *str, int in_mid);
int					have_just_digits(char *c);
int					ft_list_size(t_input *list);
void				ft_current_dir_executables(t_input *list, t_execution *data,
						char ***envi);
void				ft_path_fixing(t_execution *data, char ***envi);
void				ft_cmd_with_path(t_input *list, t_execution *data,
						char ***envi);
void				ft_execute(t_input *list, t_execution *data, char ***envi);
void				ft_execute_cmd(t_input *list, t_execution *data,
						char ***envi);
void				ft_pipe(t_input *list, t_redir *data, char ***envi,
						char ***export);
void				basic_execution(t_input *list, char ***envi);
void				ft_exec(t_input *list, char ***envi, char ***export);
void				ft_join_path_and_cmd(t_input *list, t_execution *data,
						char ***envi);
void				ft_check_access(t_execution *data);
int					ft_check_pipe_errors(t_input *list, t_pipe *pipe_data,
						char ***envi, char ***export);
t_input				*ft_skip_same_cmd(t_input *list);
void				ft_allocate_pipe_fds(t_pipe *pipe_data);
int					fork_error(t_pipe *pipe_data);
void				ft_close(t_pipe *pipe_data);
void				ft_get_exit_status(t_pipe *pipe_data);
char				**ft_remove(char **ptr, int pos);
int					ft_is_builtin(t_input *list);
int					check_in_file_permissions(t_input *list,
						t_redir *data, int i);
/*******************************************************************/
/*                         WILDCARD_UTILS                          */
/*******************************************************************/
void				the_start_of_the_beg_dual(char *copy, char **ls, int j,
						char ***holder);
void				the_start_of_the_beg(char *copy, char **ls, char ***holder);
void				find_and_collect_no_p(char **ls, char ***holder, int *j,
						char *split);
void				find_and_collect(char **ls, char ***holder, int *j,
						char *split);
char				**the_commun(char **str, char **ls);
char				**the_inner(char *str, char **ls);
char				**the_end(char *str, char **ls);
char				**the_popular_choice(char *str, char **ls);
void				check_for_hidden(char *str, char ***re);
char				**the_beg(char *str, char **ls);
void				free_triple_array(char ***c);
char				**the_repeated(char **tmp1, char **tmp2, char *str,
						int count);
char				***all_the_reapeated(char **holder, char *str, int h);
char				**collect_repeated(char *str, char **holder, char **split,
						int h);
char				**get_the_needed_array(char **holder, char **split,
						char *str);
int					hidden(char *s1, char *s2);
int					re_full_(char ***div, char ***re, int *j);
char				**make_sure(char **str, char **ls);
void				remake(char ***split, int *i, char **div);
int					count_for_ls(DIR *dir);
char				**list_current_directory_content(void);
void				wildcard(char ***split);

/********************Wildcard********************/

void				the_start_of_the_beg_dual(char *copy, char **ls, int j,
						char ***holder);
void				wildcard(char ***split);
char				**list_current_directory_content(void);
int					count_for_ls(DIR *dir);
void				remake(char ***split, int *i, char **div);
int					re_full_(char ***div, char ***re, int *j);
char				**make_sure(char **str, char **ls);
char				**the_commun(char **str, char **ls);
void				check_for_hidden(char *str, char ***re);
char				**the_beg(char *str, char **ls);
void				find_and_collect(char **ls, char ***holder, int *j,
						char *split);
void				find_and_collect_no_p(char **ls, char ***holder, int *j,
						char *split);
char				**the_popular_choice(char *str, char **ls);
char				**the_inner(char *str, char **ls);
char				**the_end(char *str, char **ls);
char				**get_the_needed_array(char **holder, char **split,
						char *str);
char				**collect_repeated(char *str, char **holder, char **split,
						int h);
char				***all_the_reapeated(char **holder, char *str, int h);
char				**the_repeated(char **tmp1, char **tmp2, char *str,
						int count);
void				free_triple_array(char ***c);
void				the_start_of_the_beg(char *copy, char **ls, char ***holder);
/****************/

void				minishell(char ***env, char ***export);
void				parse_phil_list_and_excute(char **copy, char ***env,
						char ***export);
void				parse_it(char **copy, char ***env, char ***split);
void				split_and_join(char ***split);
void				re_split(char ***tmp, char **split, int *j);
void				signals(int signum);
void				sigint(void);
char				**parsing(char **input, char **env);
int					last_check(char **str);
int					check_error(char **str, int i);
void				free_list(t_input *list);
t_input				*work_time(char **split);
int					ft_strmegacount(char **c);
void				phil_list(t_input **list, char **split);
void				disable_some_checks(t_input **list);
void				check_ambiguous(t_input **list);
void				phil_the_list(t_input **list, char **split);
void				list_details(char **split, t_input **list, int *i, int *m);
void				list_args(char **split, t_input **list, int i, int *m);
void				list_cmd(char **split, t_input **list, int i, int *m);
void				list_in(char **split, t_input **list, int i);
void				list_heardoc(char **split, t_input **list, int i);
void				list_append(char **split, t_input **list, int i);
void				ambiguous_starter_pack(char ***split);
void				exchange(char **ptr, char c, char b);
int					mega_counter(char **str, char c);
t_input				*append(t_input *list, int count);
void				init_list(t_input **list, int count);
int					fast_check(char *input);

int					error_detected(void);
void				shlvl(char ***env, int c);
void				expand(char ***str_pro_max, char **env);
void				should_i_expand(t_expand *expand, char ***str_pro_max,
						char **env);
void				expand_after_redirections(t_expand *expand,
						char ***str_pro_max, char **env);
void				fill_str(t_expand *expand, char ***str_pro_max, char **env);
void				expand_exit_stat(t_expand *expand, char **env);
void				start_expanding(t_expand *expand, char ***str_pro_max,
						char **env);
void				store_after_expand_var(char *tmp2, int *m, char **str);
char				*take_variable_from_env(char **env, int k,
						char *str_pro_max, int h);
void				get_size_to_expand(char ***str, char ***str_pro_max,
						char **env);
int					get_len_to_allocate(char ***str_pro_max, int i, char **env);
int					len_from_env_(char **env, int *j);
int					len_from_env(char ***str_pro_max, char **env, int i,
						int *j);
void				array_expander(char **ptr, char **env);
void				time_to_expand(t_expand *expand, char **ptr, char **env);
void				expand_exit_stat_array(t_expand *expand, char **env);
void				the_expander(t_expand *expand, char **ptr, char **env);
void				expand_exit_stat_size(t_expand *expand, char **env);
void				the_array_size_to_expand(t_expand *expand, char **ptr,
						char **env);
void				no_extra_(char **ptr, char c);
void				replace_spaces(char **ptr);
int					checking_direction(char *str, char *behind_str, char **env);
int					recursive_untill_found(char *str, char **env);
int					recursive_why_not(char *str, char **env);
int					checking_direction_expand(char *str, char **env);
int					in_env(char *ptr, char **env, int flag);
char				**fill(char **str);
void				make_some_space(char **str);
int					size_to_allocate(char **str);
void				space_char(char **tmp, int *i, int *j, char c);
void				space_append_heardoc(char **tmp, int *i, int *j, int type);
void				no_etxra_qoutes(char ***str);
void				delete_last_spaces(char ***str);
void				no_surounded_anymore(char **str);
void				disable(char **str, char c);
void				check_delete(char **str);
void				delete_them_inside(char **ptr, char c);
void				delete_the_chosen(t_expand *var, char **ptr,
						int number_of_char, char c);
char				dual(char c);
void				printer(char **ptr);
void				the_joiner(char ***str_pro_max);
void				delete_array_form_double_array(int *i, char ***str_pro_max);
char				**ultra_split(char **new_str, char **input);
void				make_space_split_join(char **new_str, char ***split, int i);
void				free_double_array(char **c);
void				i_should_replace_them(char **input);
void				i_should_replace_single(t_parse *pars, char **input);
void				should_i_replace_them(char **input);
void				search_and_replace(t_parse *pars, char **input);
char				**split_without_weast(char **input);
void				split_without_weast_utils(t_parse *pars, char ***new_str,
						char **input);
void				delete_non_sense(char **input);
void				look_for_partner(t_parse *pars, char ***new_str,
						char **input);
int					ft_simularity_len(char *str, char c);
void				delete_them(char **input, int start, int end);
void				delete_both(char **input, int start, int end, char c);
char				*take_copy(char *s1, int start, int end);
int					char_counter(const char *co, char c);
void				error_print(char *s1, char *s2);
int					surounded_by(char *str, char c);
char				*clean_copy(char *c);
int					max_len(char **str);
void				delete_both_double(t_parse *pars, char **input);
void				d_delete(char **input);
void				delete_both_single(t_parse *pars, char **input);
void				s_delete(char **input);
void				look_for_partner(t_parse *pars, char ***new_str,
						char **input);
void				list_out(char **split, t_input **list, int i);
int					catch_you(char **str);
void				creat_the_expanded_copy(t_expand *expand,
						char ***str_pro_max, char **env);

#endif