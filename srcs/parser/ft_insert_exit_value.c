/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_exit_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_insert_exit_value(t_expand_data *data,
	int val, char *prev_str)
{
	char	*str_val;

	printf("INTERROGANTE\n");
	str_val = ft_itoa(val);
	ft_insert_env_value(data, str_val, prev_str);
	free(str_val);
}
