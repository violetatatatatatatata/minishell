/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:45 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:47 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_expand_braced_var(t_expand_data *data)
{
	int		start;
	int		sub_end;
	char	*name;
	char	*prev_str;

	sub_end = *data->index - 1;
	start = *data->index + 1;
	(*data->index)++;
	while (ft_isalnum(data->content[*data->index])
		|| data->content[*data->index] == '_')
		(*data->index)++;
	if (data->content[*data->index] != '}')
		return ;
	name = ft_strndup(data->content + start, *data->index - start);
	prev_str = ft_substr(data->content, *data->sub_start,
			sub_end - *data->sub_start);
	ft_handle_env_var(data, &name, prev_str);
	*data->sub_start = *data->index + 1;
	if (name)
		free(name);
	free(prev_str);
}

static void	ft_expand_simple_var(t_expand_data *data)
{
	int		start;
	int		sub_end;
	int		tmp_start;
	char	*name;
	char	*prev_str;

	sub_end = *data->index;
	start = *data->index;
	while (ft_isalnum(data->content[*data->index])
		|| data->content[*data->index] == '_')
		(*data->index)++;
	name = ft_strndup(data->content + start, *data->index - start);
	tmp_start = (*data->sub_start);
	if (*data->sub_start > 0)
	{
		tmp_start = (*data->sub_start) - 1;
		sub_end++;
	}
	prev_str = ft_substr(data->content, tmp_start,
			sub_end - *data->sub_start - 1);
	printf("--- SubStart: %i, Len: %i\n", tmp_start, sub_end - *data->sub_start - 1);
	printf("Expand simple, Prev_str: %s\n", prev_str);
	ft_handle_env_var(data, &name, prev_str);
	*data->sub_start = *data->index + 1;
	if (name)
		free(name);
	free(prev_str);
	(*data->index)--;
	printf("Current index: %i\n", (*data->index));
}

void	ft_expansion(t_expand_data *data)
{
	int	sub_end;

	sub_end = (*data->index)++;
	if (sub_end > 0 && *data->sub_start != 0)
		sub_end--;
	if (data->content[*data->index] == '{')
		ft_expand_braced_var(data);
	else if (ft_isalpha(data->content[*data->index])
		|| data->content[*data->index] == '_')
		ft_expand_simple_var(data);
}
