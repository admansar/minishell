/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:52:20 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/05/13 14:46:18 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


#define OUTPUT 1
#define INPUT 3
#define HERDOC 4
#define APPEND 2

typedef struct s_redirection
{
	int				type;
	int				position; 
	char			**file_name;
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
void	ft_pipe(t_input *list);
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
int	ft_unset_name_checker(char *str);
int	ft_export_name_checker(char *str);

/********************BUILT-IN UITLS********************/
int		ft_in_env(char *ptr, char **env);
char	*ft_create_var(char *name, char *value);
void	ft_update_value_env(char *arr , char ***export, int pos);
char **fill(char **str);



/********************UTILS********************/
int	ft_strcmp(const char *s1, const char *s2);

#endif