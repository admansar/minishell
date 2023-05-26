
#include "minishell.h"

void	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
	{
		ft_printf("bash : %s\n", strerror(errno));
		return ;
	}
	printf("%s\n", path);
	g_vars.g_exit_status = 0;
	return ;
}
