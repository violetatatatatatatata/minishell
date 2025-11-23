/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_controlop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:05:26 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 02:05:27 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_controlop(const char *str)
{
	if (ft_strcmp(s, "||") == 0 || ft_strcmp(s, "&&") == 0
		|| ft_strcmp(s, "&") == 0 || ft_strcmp(s, ";") == 0
		|| ft_strcmp(s, ";;") == 0 || ft_strcmp(s, "(") == 0
		|| ft_strcmp(s, ")") == 0 || ft_strcmp(s, "|") == 0
		|| ft_strcmp(s, "!") == 0)
		return (1);
	return (0);
}
