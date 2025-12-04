/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:45:21 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/25 19:57:23 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(void)
{
	printf("%s------------------------------------------------\n", COLOR3);
	printf("%s░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", COLOR0);
	printf("%s░░░░░░░▒▒▒▒▒┌─┐┌─┐▒▒▒▒▒▒▒┌┐▒▒▒▒┌┐┌┐▒▒▒▒▒▒░░░░░░░\n", COLOR1);
	printf("%s░░░░░░░▒▒▒▒▒││└┘││▒▒▒▒▒▒▒││▒▒▒▒││││▒▒▒▒▒▒░░░░░░░\n", COLOR2);
	printf("%s░░░░░░░▒▒▒▒▒│┌┐┌┐├┬─┐┌┬──┤└─┬──┤│││▒▒▒▒▒▒░░░░░░░\n", COLOR3);
	printf("%s░░░░░░░▒▒▒▒▒│││││├┤┌┐┼┤──┤┌┐││─┤│││▒▒▒▒▒▒░░░░░░░\n", COLOR4);
	printf("%s░░░░░░░▒▒▒▒▒││││││││││├──│││││─┤└┤└┐▒▒▒▒▒░░░░░░░\n", COLOR5);
	printf("%s░░░░░░░▒▒▒▒▒└┘└┘└┴┴┘└┴┴──┴┘└┴──┴─┴─┘▒▒▒▒▒░░░░░░░\n", COLOR6);
	printf("%s░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", COLOR7);
	printf("%s------------------------------------------------\n", COLOR3);
	printf("%s  - - - - - - - - - - - - - - - - - - - - -  - -\n", COLOR2);
	printf("%s░░░░░░░    /)  /) ~ ┏━━━━━━━━━━━━━━┓     ░░░░░░░\n", COLOR2);
	printf("%s░░░░░░░   ( •-• ) ~  Violeta & Alex      ░░░░░░░\n", COLOR2);
	printf("%s░░░░░░░    /づづ  ~ ┗━━━━━━━━━━━━━━┛     ░░░░░░░\n", COLOR2);
	printf("%s  - - - - - - - - - - - - - - - - - - - - -  - -\n", COLOR2);
	printf("%s", RESET);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	*prompt(t_shell *data)
{
	char	buff[PATH_MAX];
	char	*user;
	char	*cwd;
	char	*p;

	user = ft_getenv("USER", data->env);
	if (!user)
		user = "minishell";
	cwd = ft_getenv("PWD", data->env);
	if (!cwd)
		cwd = getcwd(buff, PATH_MAX);
	p = ft_strdup(user);
	p = ft_strjoin_free(p, ":");
	p = ft_strjoin_free(p, cwd);
	p = ft_strjoin_free(p, "$ ");
	return (p);
}
