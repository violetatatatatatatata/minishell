/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:15:52 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 01:16:24 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_msg(char *function, char *msg, int exit)
{
	printf("minishell: ");
	if (function)
		printf("%s: ", function);
	printf("%s\n", msg);
	return (exit);
}
