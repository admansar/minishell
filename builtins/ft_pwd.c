/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:35 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/03 20:17:36 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
