#include "minishell.h"

// adding my var to the env by allocating an extra space for it
void ft_add_var_to_env(char ***env, char *variable)
{
	char **new_env;
	int i;
	int j;
	int n;
	int len;

	len = ft_strcount(*env);
	new_env = (char **)ft_calloc(sizeof(char *), (len + 2));
	i = -1;
	n = 0;
	j = len - 2;
	while ((*env)[++i] && (i != j))
		new_env[i] = (*env)[i];
	new_env[i] = (*env)[i];
	n = ++i;
	new_env[n++] = ft_strdup(variable);
	new_env[n] = (*env)[i];
	free(*env);
	(*env) = new_env;
}

// create a char* var -----> "name=value"
char *ft_create_var(char *name, char *value)
{
	char *var;
	int len;
	int i;
	int j;

	len = ft_strlen(name) + ft_strlen(value);
	var = ft_calloc(sizeof(char), len + 1);
	i = -1;
	if (name)
		while (name[++i])
			var[i] = name[i];
	j = 0;
	if(value)
		while (i < len)
			var[i++] = value[j++];
	return (var);
}

// check if my var is in the envirement
int  ft_in_env(char *str, char **env)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen (str)) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int ft_char_checker(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_get_var_name(char *var, char **var_name)
{
	int ret;
	int len;

	ret = ft_char_checker(var, '=');
	if (ret == -1)
	{
		len = ft_strlen (var);
		*var_name = take_copy(var, 0 , len);
	}
	else
		*var_name = take_copy(var, 0, ret - 1);
}


void	ft_get_var_value(char *var, char *var_name, char **var_value)
{
	int i;
	int ret;
	int len;

	ret = ft_char_checker(var, '=');
	if (ret == -1)
		*var_value = NULL;
	else
	{
		ret++;
		len = ft_strlen(var) - ft_strlen(var_name);
		*var_value = (char *)ft_calloc(sizeof(char), len + 3);
		i = -1;
		while (++i < len)
			(*var_value)[i] = var[i + ret];
	}
}

int ft_get_var(char *var, char **name, char **value)
{
	int i;
	int ret;
	int len;

	ret = ft_char_checker(var, '=');
	if (ret == -1)
	{
		len = ft_strlen (var);
		*name = take_copy(var, 0 , len);
		*value = NULL;
		if (ft_simularity_len(var, '+') == len - 1)
		return (-13);
	}
	else
	{
		ret++;
		*name = (char *)ft_calloc(sizeof(char), ret + 1);
		i = -1;
		while (++i < ret)
			(*name)[i] = var[i];
		len = ft_strlen(var) - ft_strlen(*name);
		*value = (char *)ft_calloc(sizeof(char), len + 3);
		i = -1;
		while (++i < len)
			(*value)[i] = var[i + ret];
	}
	return (0);
}

int	ft_unset_name_checker(char *str)
{
	int i;
	
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (-1);
	i = 1;

	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	ft_export_name_checker(char *str)
{
	int i;
	
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (-1);
	i = 1;

	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_' || str[i] == '=' ||
		(str[i] == '+' && (str[i + 1] == '=' || str[i + 1] == '\0')))
			i++;
		else
			return (-1);
	}
	return (0);
}

void	ft_export_printer(char **export)
{
	int i;
	char *tmp1;
	char *tmp2;
	int len;

	i = 0;
	while (export[i])
	{
		len = ft_simularity_len(export[i], '=');
		tmp1 = take_copy(export[i], 0, len - 1);
		tmp2 = take_copy(export[i], len + 1, ft_strlen(export[i]));
		if (ft_char_checker(export[i], '=') == -1)
			printf ("declare -x %s\n", tmp1);
		else
			printf ("declare -x %s=\"%s\"\n", tmp1, tmp2);
		free (tmp1);
		free (tmp2);
		i++;
	}
}

char	**ft_join_double_ptr_to_ptr(char *str, char **arr1)
{
	int len;
	int i;
	char	**joined;

	len = ft_strcount(arr1);
	joined = (char **)ft_calloc(sizeof(char *), len + 2);
	i = -1;
	joined[0] = ft_strdup(str);
	while (arr1[++i])
		joined[i + 1] = ft_strdup(arr1[i]);
	free_double_array(arr1);
	return (joined);
}

// join double array with a single array
char	**ft_join_ptr_to_double_ptr(char **arr1, char *str)
{
	int len;
	int i;
	char	**joined;

	len = ft_strcount(arr1);
	joined = (char **)ft_calloc(sizeof(char *), len + 2);
	i = -1;
	while (arr1[++i])
		joined[i] = ft_strdup(arr1[i]);
	joined[i] = ft_strdup(str);
	free_double_array(arr1);
	return (joined);
}

// join 2 double pointer
char	**ft_double_array_joiner(char **arr1, char **arr2)
{
	int len;
	int i;
	int j;
	char	**joined;

	len = ft_strcount(arr1) + ft_strcount(arr2) + 1;
	joined = (char **)ft_calloc(sizeof(char *), len + 1);
	i = -1;
	if (arr1)
		while (arr1[++i])
			joined[i] = arr1[i];
	j = -1;
	if (arr2)
		while (arr2[++j])
			joined[i + j] = arr2[j];
	return (joined);
}

// search for a '+' in my string and create new str that does not contain the '+'
void	ft_clean_up_name(char **str)
{
	int i;
	int	ret;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while (str[i])
	{
		ret = ft_char_checker(str[i], '+');
		if (ret >= 0)
		{
			tmp = take_copy(str[i], 0 , ret - 1);
			tmp1 = take_copy(str[i], ret + 1 , ft_strlen(str[i]));
			free(str[i]);
			str[i] = ft_strjoin(tmp, tmp1);
			free(tmp);
			free(tmp1);
		}
		i++;
	}
	
}

void	ft_clean_up_vars(char ***export)
{
	int i;
	int	ret;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while ((*export)[i])
	{
		ret = ft_char_checker((*export)[i], '+');
		if (ret >= 0)
		{
			tmp = take_copy((*export)[i], 0 , ret - 1);
			tmp1 = take_copy((*export)[i], ret + 1 , ft_strlen((*export)[i]));
			(*export)[i] = ft_str_join(tmp, tmp1);
		}
		i++;
	}
}


char **ft_check_env_var(char **valid_export_vars)
{
	char	**env_vars;
	int		i;
	int		j;
	int		count;
	int		*arr;
	int		len;

	len = ft_strcount(valid_export_vars) + 1;
	arr = (int *)ft_calloc(sizeof(int) , len);
	i = -1;
	count = 0;
	while(valid_export_vars[++i]) 
	{
		if (ft_char_checker(valid_export_vars[i], '=') >= 0)
		{
			arr[i] = 1;
			count++;
		}
	}
	env_vars = (char **)ft_calloc(sizeof(char *), count + 1);
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (arr[i])
		{
			env_vars[j] = ft_strdup(valid_export_vars[i]);
			j++;
		}
	}
	free(arr);
	return(env_vars);
}

void	ft_update_value_env(char *arr , char ***export, int pos)
{
	free((*export)[pos]);
	(*export)[pos] = ft_strdup(arr);
}


void ft_export(char ***env, t_input *list, char ***export)
{
	char 		**valid_export_vars;
	char		**valid_env_vars;
	int			exist;
	char		*tmp_name;
	char		*tmp_value;
	int			var_nbr;
	int			j;
	int			i;
	int			ret;
	
	if (!list->arg[0])
	{
		ft_export_printer(*export);
		return ;
	}
	var_nbr = ft_strcount (list->arg);
	valid_export_vars = ft_calloc (sizeof(char *), var_nbr + 1);
	i = 0;
	j = 0;
	while (list->arg[i])
	{
		ret = ft_get_var(list->arg[i], &tmp_name, &tmp_value);
		if(ft_export_name_checker(tmp_name) == -1 || ret == -13)
		{
			ft_printf("bash: export: `%s': not a valid identifier\n", list->arg[i]);
		}
		else
		{
			valid_export_vars[j] = ft_strdup(list->arg[i]);
			ft_clean_up_name(&(valid_export_vars[j]));
			j++;
		}
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	valid_env_vars = ft_check_env_var(valid_export_vars);
	i = 0;
	while (valid_export_vars[i])
	{
		ft_get_var_name(valid_export_vars[i], &tmp_name);
		ft_get_var_value(valid_export_vars[i], tmp_name, &tmp_value);
		exist = ft_in_env(tmp_name, *export);
		if (exist == -1)
			*export = ft_join_ptr_to_double_ptr(*export, valid_export_vars[i]);
		else if (tmp_value)
			ft_update_value_env (valid_export_vars[i] , export, exist);
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	i = 0;
	while (valid_env_vars[i])
	{
		ft_get_var_name(valid_env_vars[i], &tmp_name);
		ft_get_var_value(valid_env_vars[i], tmp_name, &tmp_value);
		exist = ft_in_env(tmp_name, *env);
		if (exist == -1)
			*env = ft_join_ptr_to_double_ptr(*env, valid_env_vars[i]);
		else if (tmp_value)
			ft_update_value_env (valid_env_vars[i] , env, exist);
		free(tmp_name);
		free(tmp_value);
		i++;
	}
	in_env(NULL, *env, 1);
	free_double_array(valid_env_vars);
	free_double_array(valid_export_vars);
}
