/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:03 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(const char *name, char **env)
{
	size_t	name_len;
	int		i;
	char	*equal_sign;
	size_t	var_name_len;

	if (name == NULL || env == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign == NULL)
			continue ;
		var_name_len = equal_sign - env[i];
		if (var_name_len == name_len
			&& ft_strncmp(env[i], (char *)name, name_len) == 0)
			return (equal_sign + 1);
		i++;
	}
	return (NULL);
}
