#include "minishell.h"

char	**ft_remove (char **ptr, int pos)
{
	char	**new_ptr;
	int len;
	int	i;
	int	j;

	len = ft_strcount(ptr);
	new_ptr = (char **)ft_calloc (sizeof(char *), len + 1);
	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (i == pos)
			i++;
		else
		{
			new_ptr[j] = ft_strdup(ptr[i]);
			i++;
			j++;
		}
	}
	free_double_array(ptr);
	return (new_ptr);
}

void	ft_unset(char ***env, t_input *list, char ***export)
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
	(void)export;
	(void)env;
	
	var_nbr = ft_strcount (list->arg);
	valid_export_vars = ft_calloc (sizeof(char *), var_nbr + 1);
	i = 0;
	j = 0;
	while (list->arg[i])
	{
		ret = ft_get_var(list->arg[i], &tmp_name, &tmp_value);
		if(ft_name_checker(tmp_name) == -1 || ret == -13)
		{
			printf("bash: unset: `%s': not a valid identifier\n", list->arg[i]);
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
		exist = ft_in_env(tmp_name, *export);
		if (exist >= 0)
		{
			*export = ft_remove(*export, exist);
		}
		free(tmp_name);
		i++;
	}
	i = 0;
	while (valid_env_vars[i])
	{
		ft_get_var_name(valid_env_vars[i], &tmp_name);
		exist = ft_in_env(tmp_name, *env);
		if (exist >= 0)
			*env = ft_remove(*env, exist);
		free(tmp_name);
		i++;
	}

	free_double_array(valid_env_vars);
}
