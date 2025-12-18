/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/18 16:19:31 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_parse(char *prompt, t_shell *data)
{
	char	**tokens;
	t_list	*cmd_list;

	tokens = ft_tokenize(prompt);
	cmd_list = ft_split_tokens(tokens);
	free(tokens);
	ft_expand_dolar(&cmd_list, data);
	ft_remove_quotes(cmd_list);
	cmd_list = ft_build_cmd_table(cmd_list);
	ft_expand_red(cmd_list, data);
	return (cmd_list);
}
