/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utils.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/12/17 20:06:24 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/12/17 20:06:39 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <minishell.h>

int	ft_args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->right_side;
	}
	return (i);
}
