/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:55:27 by aalcaide          #+#    #+#             */
/*   Updated: 2025/12/02 12:27:59 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*ft_get_env_val(char *s, t_shell *data, int *len)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	name = ft_substr(s, 0, i);
	value = ft_getenv(name, data->env);
	free(name);
	if (!value)
		value = "";
	*len = i;
	return (value);
}

static void	append_char(char **res, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*res, buf);
	free(*res);
	*res = tmp;
}

static void	expand_env(char **res, char **src, t_shell *data)
{
	char	*val;
	char	*tmp;
	int		len;

	val = ft_get_env_val(*src + 1, data, &len);
	tmp = ft_strjoin(*res, val);
	free(*res);
	*res = tmp;
	*src += len + 1;
}

void	ft_expand_heredoc(char **line, t_shell *data)
{
	char	*src;
	char	*result;

	src = *line;
	result = ft_strdup("");
	while (*src)
	{
		if (*src == '$' && ft_isalpha(*(src + 1)))
			expand_env(&result, &src, data);
		else
		{
			append_char(&result, *src);
			src++;
		}
	}
	free(*line);
	*line = result;
}
