/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:05:41 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 02:05:42 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_redop(const char *str)
{
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0
		|| ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, "<>") == 0 || ft_strcmp(s, "&>") == 0
		|| ft_strcmp(s, "2>&1") == 0)
		return (1);
	return (0);
}
