/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:08:07 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/15 17:17:01 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	bt_pwd(t_shell *data)
{
	char	*pwd;
	char	*cwd;

	pwd = ft_getenv("PWD", data->env);
	if (pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			ft_putendl_fd(cwd, STDOUT_FILENO);
			free(cwd);
		}
		else
			perror("minishell: pwd: error: invalid cwd\n");
	}
}
